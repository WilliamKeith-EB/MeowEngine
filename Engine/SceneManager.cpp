#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "Locator.h"
#include "Logger.h"

meow::SceneManager::SceneManager(Renderer& renderer)
	: m_Renderer{ renderer } {

}

meow::SceneManager::~SceneManager() {

	for (auto scenePair : m_pScenes) {

		delete scenePair.second;
	}
}

void meow::SceneManager::Update() {

	assert(m_pActiveScene);
	m_pActiveScene->RootUpdate();
}

void meow::SceneManager::AddScene(Scene* pScene) {

	auto succes = m_pScenes.emplace(std::make_pair(pScene->GetName(), pScene));

	if (!succes.second) {

		LOGGER.LogWarning("Scene: " + pScene->GetName() + " couldn't be added to the scene manager because an entry with that name already exists.");
		return;
	}

	pScene->RootInitialize();
}

void meow::SceneManager::SetSceneActive(const std::string& name) {

#ifdef _DEBUG
	if (m_pScenes.find(name) == m_pScenes.end())
		LOGGER.LogError("The scene you are trying to set active does not exist");
#endif
	m_pActiveScene = m_pScenes[name];
	m_Renderer.SetRenderComponents(m_pActiveScene->m_pRenderComponents, m_pActiveScene->m_NrOfRenderComponents, m_pActiveScene->m_pRenderComponentTable);
}

meow::Scene* meow::SceneManager::GetActiveScene() const {

	return m_pActiveScene;
}
