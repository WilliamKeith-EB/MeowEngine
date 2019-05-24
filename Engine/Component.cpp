#include "pch.h"
#include "Component.h"

void meow::Component::AddToGameObject(GameObject* pGameObject) {

	m_pGameObject = pGameObject;
}
