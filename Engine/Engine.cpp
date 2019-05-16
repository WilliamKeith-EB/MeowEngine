#include "pch.h"
#include "Engine.h"
#include "ConfigLoader.h"
#include "DoubleLinkAllocator.h"
#include "Game.h"

#include <SDL.h>
#include <chrono>

void Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	ConfigLoader configLoader{ "../Data/Config/" };
	auto data = configLoader.GetConfigData();
	
	StackAllocator* pFrameAllocator = new StackAllocator{ data.memory.frameAllocSize };
	Locator::Provide(pFrameAllocator);

	m_pWindow = SDL_CreateWindow(

		data.window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(data.window.width),
		int(data.window.height),
		SDL_WINDOW_OPENGL
	);

	if (m_pWindow == nullptr) {

		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	// make renderer and initialize window
	m_Renderer.Initialize(m_pWindow);
}

void Engine::Cleanup() {

	auto& frameAllocator = FRAMEALLOC;
	delete &frameAllocator;

	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Engine::Run(Game* pGame) {

	Logger logger = Logger();
	Locator::Provide(&logger);
	Initialize();

	// local scope to auto "delete" local variables to this scope
	{
		Time time{};
		InputHandler inputHandler{};
		SceneManager sceneManager{};

		Locator::Provide(&time);
		Locator::Provide(&inputHandler);
		Locator::Provide(&sceneManager);

		pGame->LoadGame();

		bool continueGame{ true };
		auto previousTime = std::chrono::high_resolution_clock::now();
		while (continueGame) {
			FRAMEALLOC.Reset(); // reset the frame allocator -> clear the buffer

			auto currentTime = std::chrono::high_resolution_clock::now();
			time.m_DeltaT = std::chrono::duration<float>(currentTime - previousTime).count();
			time.m_FPS = 1.0f / time.m_DeltaT;

			// Process input
			continueGame = inputHandler.ProcessInput();

			// update
			sceneManager.Update();

			// render
			m_Renderer.Render();

			previousTime = currentTime;
		}

		Cleanup();
	}
}
