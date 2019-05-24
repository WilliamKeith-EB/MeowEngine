#include "pch.h"
#include "RenderComponent.h"


meow::RenderComponent::RenderComponent(Texture2D* pTexture) 
	: m_pTexture{ pTexture } {

}

void meow::RenderComponent::AddToGameObject(GameObject* pGameObject) {

	m_pGameObject = pGameObject;
	m_pGameObject->GetComponent<TransformComponent>()->SetSize(m_pTexture->GetDimensions());
}

void* meow::RenderComponent::operator new(size_t size) {

	return FRAMEALLOC.Acquire(size);
}

void meow::RenderComponent::operator delete(void* ptr) {

	if (!FRAMEALLOC.IsInStack(ptr))
		((RenderComponent*)ptr)->m_pGameObject->GetScene()->RemoveRenderComponent((RenderComponent*)ptr);
}

void meow::RenderComponent::Render()
{
	m_pTexture->Render(m_pGameObject->GetComponent<TransformComponent>()->GetTransformMatrix());
}
