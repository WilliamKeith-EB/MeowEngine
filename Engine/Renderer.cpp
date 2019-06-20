#include "pch.h"
#include "Renderer.h"
#include "Locator.h"
#include "Logger.h"
#include "CameraComponent.h"
#include "ConfigLoader.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "DebugRenderer.h"

void meow::Renderer::Initialize(SDL_Window* pWindow) {

	// create openGL context
	m_Context = SDL_GL_CreateContext(pWindow);
	if (m_Context == nullptr)
	{
		LOGGER.LogError(SDL_GetError());
		return;
	}

	if (CONFIGDATA.window.useVSync)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			LOGGER.LogError(SDL_GetError());
			return;
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, CONFIGDATA.window.width, 0, CONFIGDATA.window.height); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(CONFIGDATA.window.width), int(CONFIGDATA.window.height));

	// Set the Model view matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void meow::Renderer::Render() {

	glm::vec4 backgroundColor{ CAMERA.GetBackgroundColor() };
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	// sort render components according to render depth
	QuickSortComponents(0, *m_pNrOfActiveRenderComponents - 1);

	glm::mat4x4 cameraTransform = CAMERA.GetGameObject()->GetComponent<TransformComponent>()->GetTransformMatrix();
	cameraTransform = glm::inverse(cameraTransform);

	glPushMatrix();
	glMultMatrixf(&cameraTransform[0].x);

	for (int i{}; i < *m_pNrOfActiveRenderComponents; ++i) {

		m_pRenderComponents[i].Render();
	}
#ifdef _DEBUG
	DEBUGRENDERER.Render();
#endif

	glPopMatrix();
}

void meow::Renderer::Cleanup()
{
	SDL_GL_DeleteContext(m_Context);
}

void meow::Renderer::SetRenderComponents(RenderComponent_Internal* pRenderComponents, int& nrOfActiveRenderComponents, std::vector<std::pair<RenderComponent_Internal*, bool>>* pRenderComponentTable) {

	m_pRenderComponents = pRenderComponents;
	m_pNrOfActiveRenderComponents = &nrOfActiveRenderComponents;
	m_pRenderComponentTable = pRenderComponentTable;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
 array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int meow::Renderer::PartitionComponents(int low, int high) {

	float pivot = GetDepth(m_pRenderComponents[high]); // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is bigger than or 
		// equal to pivot  -> sorting from 1.0f to 0.0f
		if (GetDepth(m_pRenderComponents[j]) >= pivot)
		{
			i++;    // increment index of smaller element 
			Swap(&m_pRenderComponents[i], &m_pRenderComponents[j]);
		}
	}
	Swap(&m_pRenderComponents[i + 1], &m_pRenderComponents[high]);
	return (i + 1);
}

float meow::Renderer::GetDepth(const RenderComponent_Internal& renderComponent) const {

	return renderComponent.m_pGameObject->GetComponent<TransformComponent>()->GetRenderDepth();
}

void meow::Renderer::Swap(RenderComponent_Internal* a, RenderComponent_Internal* b)
{
	RenderComponent_Internal t = *a;
	*a = *b;
	*b = t;
}


/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void meow::Renderer::QuickSortComponents(int low, int high) {

	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = PartitionComponents(low, high);

		// Separately sort elements before 
		// partition and after partition 
		QuickSortComponents(low, pi - 1);
		QuickSortComponents(pi + 1, high);
	}
}
