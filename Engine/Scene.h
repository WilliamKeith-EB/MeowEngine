#pragma once
#include "RenderComponent.h"

namespace meow {

	class GameObject;
	class ColliderComponent;

	class Scene
	{
		friend class RenderComponent;
		friend class RenderComponent_Internal;
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

		RenderComponent_Internal* m_pRenderComponents;
		int m_NrOfRenderComponents;
		const int m_MaxNrRenderComponents;
		std::vector<std::pair<RenderComponent_Internal*, bool>>* m_pRenderComponentTable;

		RenderComponentIndex AddRenderComponent(RenderComponent_Internal* pRenderComponent);
		void RemoveRenderComponent(RenderComponentIndex renderComponentIndex);
		void RemoveRenderComponent(RenderComponent_Internal* pRenderComponent);
		RenderComponentIndex GetIndex(RenderComponent_Internal* pRenderComponent) const;
		RenderComponentIndex GetFreePlace();
		RenderComponent_Internal* GetRenderComponent(RenderComponentIndex index);

		void AddGameObject(GameObject* pObject);
		void RemoveGameObject(GameObject* pObject);
		void AddCollider(ColliderComponent* pCollider);
		void RemoveCollider(ColliderComponent* pCollider);
	};

}
