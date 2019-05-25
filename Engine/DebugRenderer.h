#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)

namespace meow {

	class ColliderComponent;

	class DebugRenderer
	{
	public:
		DebugRenderer();
		virtual ~DebugRenderer() = default;

		void AddCollider(ColliderComponent* pCollider);
		void RemoveCollider(ColliderComponent* pCollider);

		void SetColor(const glm::vec4& color) { m_Color = color; }
		void SetLineWidth(float lineWidth) { m_LineWidth = lineWidth; }

		const glm::vec4& GetColor() const { return m_Color; }
		float GetLineWidth() const { return m_LineWidth; }

		void Render();

	protected:
		std::vector<ColliderComponent*> m_pColliders;
		glm::vec4 m_Color;
		float m_LineWidth;
	};


}