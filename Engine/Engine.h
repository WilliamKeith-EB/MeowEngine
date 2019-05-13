#pragma once
#include "Renderer.h"

struct SDL_Window;

class Engine final {

public:

	Engine() = default;
	~Engine() = default;

	Engine(const Engine& other) = delete;
	Engine(Engine&& other) noexcept = delete;
	Engine& operator=(const Engine& other) = delete;
	Engine& operator=(Engine&& other) noexcept = delete;

	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();

private:
	SDL_Window* m_pWindow;
	Renderer m_Renderer;
};