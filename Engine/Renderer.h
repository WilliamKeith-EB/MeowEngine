#pragma once
#include "RenderComponent.h"

struct SDL_Window;

namespace meow {

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void Initialize(SDL_Window* pWindow);
		void Render();

		void Cleanup();

		void SetRenderComponents(RenderComponent_Internal* pRenderComponents, int& nrOfActiveRenderComponents, std::vector<std::pair<RenderComponent_Internal*, bool>>* pRenderComponentTable);
	private:
		SDL_GLContext m_Context;
		int* m_pNrOfActiveRenderComponents;
		RenderComponent_Internal* m_pRenderComponents;
		std::vector<std::pair<RenderComponent_Internal*, bool>>* m_pRenderComponentTable;

		void QuickSortComponents(int low, int high);
		int PartitionComponents(int low, int high);
		float GetDepth(const RenderComponent_Internal& renderComponent) const;
		void Swap(RenderComponent_Internal* a, RenderComponent_Internal* b);

	};
}

