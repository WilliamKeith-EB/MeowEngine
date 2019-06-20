#include "pch.h"
#include "RenderComponent.h"
#include "Locator.h"
#include "StackAllocator.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Scene.h"

meow::RenderComponent_Internal::RenderComponent_Internal(Texture2D* pTexture)
	: m_pTexture{ pTexture } {

}

void meow::RenderComponent_Internal::AddToGameObject(GameObject* pGameObject) {

	m_pGameObject = pGameObject;
	pGameObject->GetComponent<TransformComponent>()->SetSize(m_pTexture->GetDimensions());
}

void* meow::RenderComponent_Internal::operator new(size_t size) {

	return FRAMEALLOC.Acquire(size);
}

void meow::RenderComponent_Internal::operator delete(void* ptr) {

	if (!FRAMEALLOC.IsInStack(ptr))
		((RenderComponent_Internal*)ptr)->m_pGameObject->GetScene()->RemoveRenderComponent((RenderComponent_Internal*)ptr);
}

void meow::RenderComponent_Internal::Render()
{
	m_pTexture->Render(m_pGameObject->GetComponent<TransformComponent>()->GetTransformMatrix());
}

meow::RenderComponent::RenderComponent(Texture2D * pTexture)
	: m_pRenderComponent{ new RenderComponent_Internal{pTexture} }
{
}

void meow::RenderComponent::AddToGameObject(GameObject * pGameObject)
{
	m_pGameObject = pGameObject;
	m_pRenderComponent->AddToGameObject(pGameObject);
}

void meow::RenderComponent::SetRenderComponentIndex(RenderComponentIndex index)
{
	m_RenderComponentIndex = index;
}


