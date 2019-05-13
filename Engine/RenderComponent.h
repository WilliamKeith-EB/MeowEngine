#pragma once

class GameObject;

class RenderComponent final
{
public:
	RenderComponent();
	~RenderComponent();

	void AddToGameObject(GameObject* pGameObject);
	void* operator new(size_t size);
	void operator delete(void* ptr);
private:
	GameObject* m_pGameObject;
};

