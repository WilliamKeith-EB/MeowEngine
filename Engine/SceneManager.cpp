#include "pch.h"
#include "SceneManager.h"


SceneManager::SceneManager() {

}


SceneManager::~SceneManager() {

	for (auto scenePair : m_pScenes) {

		delete scenePair.second;
	}
}

void SceneManager::Update() {

	assert(m_pActiveScene);
	m_pActiveScene->Update();
}

void SceneManager::AddScene(Scene * pScene) {

	auto succes = m_pScenes.emplace(std::make_pair(pScene->GetName(), pScene));

	if (!succes.second) {

		LOGGER.LogWarning("Scene: " + pScene->GetName() + " couldn't be added to the scenemanager because an entry with that name already exists.");
	}
}

void SceneManager::SetSceneActive(const std::string& name) {

	m_pActiveScene = m_pScenes[name];
}

Scene* SceneManager::GetActiveScene() const {

	return m_pActiveScene;
}
