#pragma once

struct SDL_Window;
struct SDL_Renderer;

class Renderer final
{
public:
	Renderer() = default;
	~Renderer() = default;

	void Initialize(SDL_Window* pWindow);
	void Destroy();

	void Render();

private:
	SDL_Renderer* m_pRenderer;
};

