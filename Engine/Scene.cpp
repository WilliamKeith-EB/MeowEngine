#include "pch.h"
#include "Scene.h"
#include "ColliderComponent.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Locator.h"
#include "ConfigLoader.h"
#include <algorithm>


meow::Scene::Scene(const std::string& name)
	: m_Name{ name }
	, m_pRenderComponents{ (RenderComponent_Internal*) malloc(sizeof(RenderComponent_Internal) * CONFIGDATA.memory.maxNumberOfRenderComponents) }
	, m_pGameObjects{} 
	, m_pRenderComponentTable{ new std::vector<std::pair<RenderComponent_Internal*, bool>>() }
	, m_MaxNrRenderComponents{ CONFIGDATA.memory.maxNumberOfRenderComponents }{

	m_pGameObjects.reserve(CONFIGDATA.memory.gameObjectArrayStartSize);
}

meow::Scene::~Scene() {

	free(m_pRenderComponents);
	for (GameObject* pObject : m_pGameObjects) {

		delete pObject;
	}

	delete m_pRenderComponentTable;
}

void meow::Scene::RootInitialize() {

	GameObject* pCameraObject = new GameObject("MainCamera");
	CameraComponent* pCamera = new CameraComponent({ 0.9f, 0.9f, 0.9f, 1.0f });
	pCameraObject->AddComponent(pCamera);
	TransformComponent* pTransform = pCameraObject->GetComponent<TransformComponent>();
	pTransform->SetSize({CONFIGDATA.window.width, CONFIGDATA.window.height});
	pTransform->SetAnchor({ 0.5f,0.5f });
	pTransform->SetPosition({ CONFIGDATA.window.width /2, CONFIGDATA.window.height / 2 });
	pCameraObject->AddToScene(this);
	Locator::Provide(pCamera);

	Initialize();
}

void meow::Scene::RootUpdate() {

	// do collision
	for (int i{}; i < int(m_pColliders.size()) - 1; ++i) {

		for (int j{ i + 1 }; j < int(m_pColliders.size()); ++j) {

			m_pColliders[i]->CheckCollision(m_pColliders[j]);
		}
	}

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

RenderComponentIndex meow::Scene::AddRenderComponent(RenderComponent_Internal* pRenderComponent) {

	assert(m_NrOfRenderComponents < m_MaxNrRenderComponents);
	memcpy(&m_pRenderComponents[m_NrOfRenderComponents], pRenderComponent, sizeof(RenderComponent_Internal));
	RenderComponentIndex index = GetFreePlace();
	m_pRenderComponentTable->at(index).first = &m_pRenderComponents[m_NrOfRenderComponents++];

#ifdef _DEBUG
		if (m_NrOfRenderComponents == m_MaxNrRenderComponents)
			LOGGER.LogWarning("Array of render components is full");
#endif

	return index;
}

void meow::Scene::RemoveRenderComponent(RenderComponentIndex renderComponentIndex) {

	auto pRenderComponent = GetRenderComponent(renderComponentIndex);
	m_pRenderComponentTable->at(renderComponentIndex).second = false;
	*pRenderComponent = m_pRenderComponents[m_NrOfRenderComponents - 1];
	m_pRenderComponentTable->at(GetIndex(&m_pRenderComponents[--m_NrOfRenderComponents])).first = pRenderComponent;
}

void meow::Scene::RemoveRenderComponent(RenderComponent_Internal* pRenderComponent)
{
	auto renderComponentIndex = GetIndex(pRenderComponent);
	m_pRenderComponentTable->at(renderComponentIndex).second = false;
	*pRenderComponent = m_pRenderComponents[m_NrOfRenderComponents - 1];
	m_pRenderComponentTable->at(GetIndex(&m_pRenderComponents[--m_NrOfRenderComponents])).first = pRenderComponent;
}

RenderComponentIndex meow::Scene::GetIndex(RenderComponent_Internal* pRenderComponent) const {

	auto it = std::find_if(m_pRenderComponentTable->cbegin(), m_pRenderComponentTable->cend(), 
		[pRenderComponent](const std::pair<RenderComponent_Internal*, bool>& p) {

		return p.first == pRenderComponent;
	});
	if (it == m_pRenderComponentTable->cend()) {
#ifdef _DEBUG
		LOGGER.LogWarning("RenderComponent not found");
#endif

		return RenderComponentIndex(-1);
	}
	
	return RenderComponentIndex(it - m_pRenderComponentTable->cbegin());
}

RenderComponentIndex meow::Scene::GetFreePlace() {

	auto it =  std::find_if(m_pRenderComponentTable->begin(), m_pRenderComponentTable->end(),
		[](const std::pair<RenderComponent_Internal*, bool>& p) {

		return !p.second;
	});

	if (it == m_pRenderComponentTable->end()) {

		m_pRenderComponentTable->push_back(std::make_pair(nullptr, true));
		return RenderComponentIndex(m_pRenderComponentTable->size() - 1);
	}

	it->second = true;
	return RenderComponentIndex(it - m_pRenderComponentTable->begin());
}

meow::RenderComponent_Internal* meow::Scene::GetRenderComponent(RenderComponentIndex index)
{

	assert(index < m_pRenderComponentTable->size());
#ifdef _DEBUG

	if (!m_pRenderComponentTable->at(index).second)
		LOGGER.LogWarning("accessing invalid index");
#endif
	return m_pRenderComponentTable->at(index).first;
}

void meow::Scene::AddGameObject(GameObject* pObject) {

	m_pGameObjects.push_back(pObject);
}

void meow::Scene::RemoveGameObject(GameObject* pObject) {

	m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), pObject), m_pGameObjects.end());
}

void meow::Scene::AddCollider(ColliderComponent* pCollider) {

	m_pColliders.push_back(pCollider);
}

void meow::Scene::RemoveCollider(ColliderComponent* pCollider) {

	m_pColliders.erase(std::remove(m_pColliders.begin(), m_pColliders.end(), pCollider), m_pColliders.end());
}