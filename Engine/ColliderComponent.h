#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace meow {

	class CollisionListener;

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(const glm::vec2& localPosition, const glm::vec2& dimensions, bool isStatic, CollisionListener* pListener = nullptr, bool isTrigger = false);
		virtual ~ColliderComponent() = default;

		void Update() override {};

		const glm::vec2& GetLocalPosition() const { return m_localPosition; }
		glm::vec2 GetDimensions() const;
		bool IsTrigger() const { return m_IsTrigger; }
		CollisionListener* GetListener() const { return m_pListener; }
		glm::vec2 GetPosition() const;

		void CheckCollision(ColliderComponent* pOther);

	protected:
		glm::vec2 m_localPosition, m_Dimensions;
		bool m_IsTrigger, m_IsStatic;
		CollisionListener* m_pListener;
	};
}

