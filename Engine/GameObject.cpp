#include "pch.h"
#include "GameObject.h"


GameObject::GameObject(const std::string& name)
	: m_Name{ name } {

}

// TODO: delete children
GameObject::~GameObject() {

}

void GameObject::AddComponent(Component* pComponent) {

	if (m_pScene) {
	
		auto pBuffer = pComponent;
		pComponent = reinterpret_cast<Component*>(m_pScene->m_ComponentPool.Acquire(sizeof(pComponent)));
		*pComponent = *pBuffer;
	}

	m_pComponents.push_back(pComponent);
}

void GameObject::AddComponent(RenderComponent* pComponent) {

	if (m_pScene) {

		m_pScene->AddRenderComponent(pComponent);
	}

	m_pRenderComponent = pComponent;
}

void GameObject::AddToScene(Scene* pScene) {

	m_pScene = pScene;

	if(m_pRenderComponent)
		m_pScene->m_pRenderComponents[m_pScene->m_NrOfRenderComponents++] = *m_pRenderComponent;

	for (Component* pComponent : m_pComponents) {

		auto pBuffer = pComponent;
		pComponent = reinterpret_cast<Component*>(m_pScene->m_ComponentPool.Acquire(sizeof(pComponent)));
		*pComponent = *pBuffer;
	}

}

Scene* GameObject::GetScene() const {

	return m_pScene;
}
