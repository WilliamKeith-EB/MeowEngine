#pragma once
#include "Texture2D.h"

class GameObject;

class RenderComponent final
{
	friend class Renderer;

public:
	explicit RenderComponent(const Texture2D& texture);
	~RenderComponent() = default;

	void AddToGameObject(GameObject* pGameObject);
	GameObject* GetGameObject() const {	return m_pGameObject; }

	void* operator new(size_t size);
	void operator delete(void* ptr);
private:
	GameObject* m_pGameObject;
	Texture2D m_Texture;

	void Render();
};

