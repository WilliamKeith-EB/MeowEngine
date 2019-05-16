#pragma once
class Component;
class RenderComponent;

class GameObject final
{
public:
	GameObject(const std::string& name);
	~GameObject();

	void AddComponent(Component* pComponent);
	void AddComponent(RenderComponent* pRenderComponent);
	template<class T>
	T* GetComponent() const;

	void AddToScene(Scene* pScene);
	Scene* GetScene() const;

	void* operator new(size_t size);
	void operator delete(void* ptr);

private: 
	std::vector<Component*> m_pComponents;
	RenderComponent* m_pRenderComponent;
	std::string m_Name;
	Scene* m_pScene;
};

template<class T>
T* GameObject::GetComponent() const {

	for (Component* pComponent : m_pComponents) {

		T* pActual = dynamic_cast<T*>(pComponent);
		if (pActual)
			return pActual;
	}

	LOGGER.LogError(m_Name + " doesn't have a component of type " + typeid(T).name);

	return nullptr;
}