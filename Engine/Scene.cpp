#include "pch.h"
#include "Scene.h"


Scene::Scene(const std::string& name)
	: m_ComponentPool{1024}
	, m_Name{ name }
	, m_pRenderComponents{ new RenderComponent[50]}
	, m_pGameObjects{ (GameObject*) malloc(sizeof(GameObject) * 60) }
{
}


Scene::~Scene()
{
	delete[] m_pRenderComponents;
	free(m_pGameObjects);
}

void Scene::Update()
{
}

std::string Scene::GetName() const
{
	return m_Name;
}

RenderComponent* Scene::AddRenderComponent(RenderComponent* pRenderComponent) {

	m_pRenderComponents[m_NrOfRenderComponents++] = *pRenderComponent;
	return &m_pRenderComponents[m_NrOfRenderComponents - 1];
}

void Scene::RemoveRenderComponent(RenderComponent* pRenderComponent) {

	auto buffer = *pRenderComponent;
	*pRenderComponent = m_pRenderComponents[m_NrOfRenderComponents - 1];
	m_pRenderComponents[--m_NrOfRenderComponents] = buffer;
}

void Scene::AddGameObject(GameObject* pGameObject) {

	m_pGameObjects[m_NrOfGameObjects++] = *pGameObject;
}

void Scene::RemoveGameObject(GameObject* pGameObject) {

	auto buffer = *pGameObject;
	*pGameObject = m_pGameObjects[m_NrOfGameObjects - 1];
	m_pGameObjects[--m_NrOfGameObjects] = buffer;
}
