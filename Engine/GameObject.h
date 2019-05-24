#pragma once

namespace meow {

	class Component;
	class RenderComponent;
	class TransformComponent;

	class GameObject final
	{
	public:
		GameObject(const std::string& name = "");
		~GameObject();

		Component* AddComponent(Component* pComponent);
		void AddComponent(RenderComponent* pRenderComponent);
		template<class T>
		T* GetComponent() const;

		template<>
		RenderComponent* GetComponent<RenderComponent>() const {

			return m_pRenderComponent;
		}

		template<>
		TransformComponent* GetComponent<TransformComponent>() const {

			return m_pTransformComponent;
		}

		void AddToScene(Scene* pScene);
		Scene* GetScene() const;
		const std::string& GetName() const { return m_Name; }

		void Update();

	private:
		std::vector<Component*> m_pComponents;
		TransformComponent* m_pTransformComponent;
		RenderComponent* m_pRenderComponent;
		std::string m_Name;
		Scene* m_pScene;
	};

}

template<class T>
T* meow::GameObject::GetComponent() const {

	for (Component* pComponent : m_pComponents) {

		T* pActual = dynamic_cast<T*>(pComponent);
		if (pActual)
			return pActual;
	}

	LOGGER.LogError(m_Name + " doesn't have a component of type " + typeid(T).name());

	return nullptr;
}