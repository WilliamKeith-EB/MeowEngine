#include "pch.h"
#include "Scene.h"


Scene::Scene(const std::string& name)
	: m_ComponentPool{1024}
	, m_Name{ name }
	, m_pRenderComponents{ new RenderComponent[50]}
{
}


Scene::~Scene()
{
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
