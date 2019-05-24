#pragma once
#include <unordered_map>
#include "Renderer.h"

namespace meow {

	class Scene;

	class SceneManager final
	{
	public:
		explicit SceneManager(Renderer& renderer);
		~SceneManager();

		void Update();

		void AddScene(Scene* pScene);
		void SetSceneActive(const std::string& name);

		Scene* GetActiveScene() const;

	private:
		Scene* m_pActiveScene;
		Renderer& m_Renderer;
		std::unordered_map<std::string, Scene*> m_pScenes;
	};
}