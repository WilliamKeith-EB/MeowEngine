#include "pch.h"
#include "Scene.h"
#include <algorithm>


meow::Scene::Scene(const std::string& name)
	: m_Name{ name }
	, m_pRenderComponents{ (RenderComponent*) malloc(sizeof(RenderComponent) * CONFIGDATA.memory.maxNumberOfRenderComponents) }
	, m_pGameObjects{} {

	m_pGameObjects.reserve(CONFIGDATA.memory.gameObjectArrayStartSize);
}


meow::Scene::~Scene() {

	free(m_pRenderComponents);
	for (GameObject* pObject : m_pGameObjects) {

		delete pObject;
	}
}

void meow::Scene::RootInitialize() {

	GameObject* pCameraObject = new GameObject("MainCamera");
	CameraComponent* pCamera = new CameraComponent({ 0.0f, 0.0f, 0.5f, 1.0f });
	pCameraObject->AddComponent(pCamera);
	TransformComponent* pTransform = pCameraObject->GetComponent<TransformComponent>();
	pTransform->SetSize({CONFIGDATA.window.width, CONFIGDATA.window.height});
	pTransform->SetAnchor({0,0  });
	pCameraObject->AddToScene(this);
	Locator::Provide(pCamera);

	Initialize();
}

void meow::Scene::RootUpdate() {

	for (GameObject* pObject : m_pGameObjects) {

		pObject->Update();
	}

	Update();
}

std::string meow::Scene::GetName() const
{
	return m_Name;
}

meow::GameObject* meow::Scene::FindGameObjectWithName(const std::string& name) {

	auto it = std::find_if(m_pGameObjects.cbegin(), m_pGameObjects.cend(), 
		[&name](const GameObject* pObject) {

		if (pObject->GetName() == name)
			return true;
		
		return false;
	});

	if (it != m_pGameObjects.cend())
		return *it;
	return nullptr;
}

meow::RenderComponent* meow::Scene::AddRenderComponent(RenderComponent* pRenderComponent) {

	memcpy(&m_pRenderComponents[m_NrOfRenderComponents++], pRenderComponent, sizeof(RenderComponent));
	return &m_pRenderComponents[m_NrOfRenderComponents - 1];
}

void meow::Scene::RemoveRenderComponent(RenderComponent* pRenderComponent) {

	auto buffer = *pRenderComponent;
	*pRenderComponent = m_pRenderComponents[m_NrOfRenderComponents - 1];
	m_pRenderComponents[--m_NrOfRenderComponents] = buffer;
}

void meow::Scene::AddGameObject(GameObject* pObject) {

	m_pGameObjects.push_back(pObject);
}

void meow::Scene::RemoveGameObject(GameObject* pObject) {

	m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), pObject), m_pGameObjects.end());
}
