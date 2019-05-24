#include "pch.h"
#include "Engine.h"
#include "ConfigLoader.h"
#include "Game.h"
#include <chrono>

void meow::Engine::Initialize()
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		LOGGER.LogError(SDL_GetError());
		return;
	}

	// Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	ConfigLoader configLoader{ "../Data/Config/" };
	ConfigData* pData = new ConfigData(configLoader.GetConfigData());
	
	Locator::Provide(pData);

	m_pWindow = SDL_CreateWindow(

		pData->window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(pData->window.width),
		int(pData->window.height),
		SDL_WINDOW_OPENGL
	);

	if (m_pWindow == nullptr) {

		LOGGER.LogError(SDL_GetError());
		return;
	}



	// make renderer and initialize window
	m_Renderer.Initialize(m_pWindow);
}

void meow::Engine::Cleanup() {

	auto& configdata = CONFIGDATA;
	delete &configdata;

	m_Renderer.Cleanup();

	SDL_DestroyWindow(m_pWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void meow::Engine::Run(Game* pGame) {

	Logger logger = Logger();
	ResourceManager resourceManager{ "../Data/" };

	Locator::Provide(&logger);
	Locator::Provide(&resourceManager);

	Initialize();

	// local scope to auto "delete" local variables to this scope
	{
		Time time{};
		InputHandler inputHandler{};
		SceneManager sceneManager{m_Renderer};
		StackAllocator frameAllocator{ CONFIGDATA.memory.frameAllocSize };

		Locator::Provide(&time);
		Locator::Provide(&inputHandler);
		Locator::Provide(&sceneManager);
		Locator::Provide(&frameAllocator);

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

			SDL_GL_SwapWindow(m_pWindow);

			previousTime = currentTime;
		}
	}

	Cleanup();
}
