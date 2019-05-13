#include "pch.h"
#include "Component.h"

void Component::AddToGameObject(GameObject* pGameObject) {

	m_pGameObject = pGameObject;
}

void* Component::operator new(size_t size) {

	return FRAMEALLOC.Acquire(size);
}

void Component::operator delete(void* ptr) {

	if (!FRAMEALLOC.IsInStack(ptr))
		((Component*)ptr)->m_pGameObject->GetScene()->m_ComponentPool.Release(ptr);
}
