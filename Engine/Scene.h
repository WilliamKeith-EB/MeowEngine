#pragma once

namespace meow {

	class RenderComponent;
	class GameObject;
	class ColliderComponent;

	class Scene
	{
		friend class RenderComponent;
		friend class GameObject;
		friend class SceneManager;

	public:
		explicit Scene(const std::string& name);
		virtual ~Scene();

		void RootInitialize();
		virtual void Initialize() = 0;
		void RootUpdate();
		virtual void Update() = 0;

		std::string GetName() const;
		GameObject* FindGameObjectWithName(const std::string& name);

	private:
		std::string m_Name;

		std::vector<GameObject*> m_pGameObjects;
		std::vector<ColliderComponent*> m_pColliders;

		RenderComponent* m_pRenderComponents;
		int m_NrOfRenderComponents;

		RenderComponent* AddRenderComponent(RenderComponent* pRenderComponent);
		void RemoveRenderComponent(RenderComponent* pRenderComponent);

		void AddGameObject(GameObject* pObject);
		void RemoveGameObject(GameObject* pObject);
		void AddCollider(ColliderComponent* pCollider);
		void RemoveCollider(ColliderComponent* pCollider);
	};

}
