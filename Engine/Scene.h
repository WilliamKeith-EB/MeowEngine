#pragma once
#include "DoubleLinkAllocator.h"

class RenderComponent;
class GameObject;

class Scene
{
	friend class Component;
	friend class RenderComponent;
	friend class GameObject;

public:
	explicit Scene(const std::string& name);
	virtual ~Scene();

	virtual void Update();

	std::string GetName() const;

private:
	std::string m_Name;

	GameObject* m_pGameObjects;
	int m_NrOfGameObjects;

	RenderComponent* m_pRenderComponents;
	int m_NrOfRenderComponents;

	RenderComponent* AddRenderComponent(RenderComponent* pRenderComponent);
	void RemoveRenderComponent(RenderComponent* pRenderComponent);

	void AddGameObject(GameObject* pGameObject);
	void RemoveGameObject(GameObject* pGameObject);

	DoubleLinkAllocator m_ComponentPool;
};

