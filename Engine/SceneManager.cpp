#include "pch.h"
#include "SceneManager.h"

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

	m_pActiveScene = m_pScenes[name];
	m_Renderer.SetRenderComponents(m_pActiveScene->m_pRenderComponents, m_pActiveScene->m_NrOfRenderComponents);
}

meow::Scene* meow::SceneManager::GetActiveScene() const {

	return m_pActiveScene;
}
