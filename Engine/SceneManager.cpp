#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager(Renderer& renderer)
	: m_Renderer{ renderer } {

}

SceneManager::~SceneManager() {

	for (auto scenePair : m_pScenes) {

		delete scenePair.second;
	}
}

void SceneManager::Update() {

	assert(m_pActiveScene);
	m_pActiveScene->RootUpdate();
}

void SceneManager::AddScene(Scene* pScene) {

	auto succes = m_pScenes.emplace(std::make_pair(pScene->GetName(), pScene));

	if (!succes.second) {

		LOGGER.LogWarning("Scene: " + pScene->GetName() + " couldn't be added to the scene manager because an entry with that name already exists.");
		return;
	}

	pScene->RootInitialize();
}

void SceneManager::SetSceneActive(const std::string& name) {

	m_pActiveScene = m_pScenes[name];
	m_Renderer.SetRenderComponents(m_pActiveScene->m_pRenderComponents, m_pActiveScene->m_NrOfRenderComponents);
}

Scene* SceneManager::GetActiveScene() const {

	return m_pActiveScene;
}
