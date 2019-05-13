#pragma once
class GameObject;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Update() = 0;

	void* operator new(size_t size);
	void operator delete(void* ptr);

	void AddToGameObject(GameObject* pGameObject);

protected:
	GameObject* m_pGameObject;
};

