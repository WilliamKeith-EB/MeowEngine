#include "pch.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CollisionListener.h"

meow::ColliderComponent::ColliderComponent(const glm::vec2& localPosition, const glm::vec2& dimensions, bool isStatic, CollisionListener* pListener, bool isTrigger)
	: m_localPosition{ localPosition }
	, m_Dimensions{ dimensions }
	, m_IsTrigger{ isTrigger }
	, m_pListener{ pListener }
	, m_IsStatic{ isStatic } {


}

glm::vec2 meow::ColliderComponent::GetDimensions() const {

	auto transform = m_pGameObject->GetComponent<TransformComponent>();
	auto scale = transform->GetScale();
	scale.x *= m_Dimensions.x;
	scale.y *= m_Dimensions.y;
	return scale;
}

glm::vec2 meow::ColliderComponent::GetPosition() const {

	auto transform = m_pGameObject->GetComponent<TransformComponent>();
	auto dim = transform->GetSize();
	auto scale = transform->GetScale();
	auto anchor = transform->GetAnchor();
	anchor.x *= dim.x * scale.x;
	anchor.y *= dim.y * scale.y;
	glm::vec2 position = transform->GetPosition() - anchor + m_localPosition;
	return position;
}

void meow::ColliderComponent::CheckCollision(ColliderComponent* pOther) {

	auto pos1 = GetPosition();
	auto pos2 = pOther->GetPosition();

	auto dim1 = GetDimensions();
	auto dim2 = pOther->GetDimensions();

	if (pos1.x < pos2.x + dim2.x &&
		pos1.x + dim1.x > pos2.x &&
		pos1.y < pos2.y + dim2.y &&
		pos1.y + dim1.y > pos2.y) {

		//LOGGER.LogInfo("COLLISION");

		if (m_pListener)
			m_pListener->OnCollision();

		if (pOther->m_pListener)
			pOther->m_pListener->OnCollision();

		// collision
		if (!m_IsTrigger && !pOther->IsTrigger()) {

			// move them outwards
			if (m_IsStatic) {

			//	if(pos1.x <)
			}
		}

	//	if(m_pListener)
			
	}
}

