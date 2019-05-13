#pragma once
#include "DoubleLinkAllocator.h"

class RenderComponent;

class Scene
{
	friend class Component;
	friend class RenderComponent;
	friend class GameObject;

public:
	Scene();
	virtual ~Scene();

	virtual void Update();

	std::string GetName() const;



private:
	std::string m_Name;

	RenderComponent* m_pRenderComponents;
	int m_NrOfRenderComponents;

	RenderComponent* AddRenderComponent(RenderComponent* pRenderComponent);
	void RemoveRenderComponent(RenderComponent* pRenderComponent);

	DoubleLinkAllocator m_ComponentPool;
};

