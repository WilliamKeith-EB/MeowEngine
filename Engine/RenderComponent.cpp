#include "pch.h"
#include "RenderComponent.h"


RenderComponent::RenderComponent() {

}


RenderComponent::~RenderComponent() {

}

void RenderComponent::AddToGameObject(GameObject* pGameObject) {

	m_pGameObject = pGameObject;
}

void* RenderComponent::operator new(size_t size) {

	return FRAMEALLOC.Acquire(size);
}

void RenderComponent::operator delete(void* ptr) {

	if (!FRAMEALLOC.IsInStack(ptr))
		((RenderComponent*)ptr)->m_pGameObject->GetScene()->RemoveRenderComponent((RenderComponent*)ptr);
}
