#include "pch.h"
#include "RenderComponent.h"


RenderComponent::RenderComponent(const Texture2D& texture) 
	: m_Texture{ texture } {

}

void RenderComponent::AddToGameObject(GameObject* pGameObject) {

	m_pGameObject = pGameObject;
	m_pGameObject->GetComponent<TransformComponent>()->SetSize(m_Texture.GetDimensions());
}

void* RenderComponent::operator new(size_t size) {

	return FRAMEALLOC.Acquire(size);
}

void RenderComponent::operator delete(void* ptr) {

	if (!FRAMEALLOC.IsInStack(ptr))
		((RenderComponent*)ptr)->m_pGameObject->GetScene()->RemoveRenderComponent((RenderComponent*)ptr);
}

void RenderComponent::Render()
{
	m_Texture.Render(m_pGameObject->GetComponent<TransformComponent>()->GetTransformMatrix());
}
