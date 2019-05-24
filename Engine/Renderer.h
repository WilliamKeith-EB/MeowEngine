#pragma once

struct SDL_Window;
class RenderComponent;

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

	void Initialize(SDL_Window* pWindow);
	void Render();

	void Cleanup();

	void SetRenderComponents(RenderComponent* pRenderComponents, int& nrOfActiveRenderComponents);
private:
	SDL_GLContext m_Context;
	int* m_pNrOfActiveRenderComponents;
	RenderComponent* m_pRenderComponents;

	void QuickSortComponents(int low, int high);
	int PartitionComponents(int low, int high);
	float GetDepth(const RenderComponent& renderComponent) const;
	void Swap(RenderComponent* a, RenderComponent* b);

};

