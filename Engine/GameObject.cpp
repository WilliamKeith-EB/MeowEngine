#include "pch.h"
#include "GameObject.h"


meow::GameObject::GameObject(const std::string& name)
	: m_Name{ name } {

	AddComponent(new TransformComponent());
}

// TODO: delete children
meow::GameObject::~GameObject() {

	for (Component* pComponent : m_pComponents) {

		delete pComponent;
	}
}

meow::Component* meow::GameObject::AddComponent(Component* pComponent) {

	TransformComponent* isTransform = dynamic_cast<TransformComponent*>(pComponent);
	if (isTransform)
	{
		if (m_pTransformComponent) {

			LOGGER.LogWarning(m_Name + " already has a transformComponent");
			return nullptr;
		}

		m_pTransformComponent = isTransform;
	}

	m_pComponents.push_back(pComponent);
	pComponent->AddToGameObject(this);

	return pComponent;
}

void meow::GameObject::AddComponent(RenderComponent* pComponent) {

	if (m_pScene) {

		pComponent = m_pScene->AddRenderComponent(pComponent);
	}

	m_pRenderComponent = pComponent;
	m_pRenderComponent->AddToGameObject(this);
}

void meow::GameObject::AddToScene(Scene* pScene) {

	m_pScene = pScene;

	if (m_pRenderComponent) {

		m_pScene->AddRenderComponent(m_pRenderComponent);
	}

	pScene->AddGameObject(this);
}

meow::Scene* meow::GameObject::GetScene() const {

	return m_pScene;
}

void meow::GameObject::Update() {

	for (Component* pComponent : m_pComponents) {

		pComponent->Update();
	}
}
