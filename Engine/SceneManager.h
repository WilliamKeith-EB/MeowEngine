#pragma once
#include <unordered_map>

class Scene;

class SceneManager final
{
public:
	SceneManager();
	~SceneManager();

	void Update();

	void AddScene(Scene* pScene);
	void SetSceneActive(const std::string& name);

	Scene* GetActiveScene() const;

private:
	Scene* m_pActiveScene;
	std::unordered_map<std::string, Scene*> m_pScenes;
};

