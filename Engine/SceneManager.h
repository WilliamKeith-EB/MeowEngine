#pragma once
#include <map>

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
	std::map<std::string, Scene*> m_pScenes;
};

