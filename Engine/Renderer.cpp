#include "pch.h"
#include "Renderer.h"
#include <SDL.h>

void Renderer::Initialize(SDL_Window * pWindow) {

	m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);

	if (m_pRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Destroy() {

	if (m_pRenderer != nullptr) {

		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void Renderer::Render() {

	SDL_RenderClear(m_pRenderer);

	// render shit

	SDL_RenderPresent(m_pRenderer);
}
