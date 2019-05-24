#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#pragma warning(pop)

namespace meow {

	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		~TransformComponent() = default;

		virtual void Update() override {};

		void SetPosition(const glm::vec2& newPosition);
		void Move(const glm::vec2& displacement);
		void SetRotation(float newRotation);
		void Rotate(float addedRotation);
		void SetScale(const glm::vec2& newScale);
		void Scale(const glm::vec2& addedScale);
		void SetSize(const glm::vec2& newSize);
		void SetAnchor(const glm::vec2& newAnchor);
		void SetRenderDepth(float renderDepth);

		const glm::vec2& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }
		const glm::vec2& GetScale() const { return m_Scale; }
		const glm::vec2& GetSize() const { return m_Size; }
		const glm::vec2& GetAnchor() const { return m_Anchor; }
		const glm::mat4x4& GetTransformMatrix();
		float GetRenderDepth() const { return m_RenderDepth; }

	private:
		glm::vec2 m_Position;
		float m_Rotation; // rotation in degrees
		glm::vec2 m_Scale;
		glm::vec2 m_Size;
		glm::vec2 m_Anchor; // 0, 0 = bottom left, 1, 1 = top right
		float m_RenderDepth; // between 0 and 1

		glm::mat4x4 m_TransformMatrix;
		bool m_Dirty;

		void CalculateTransformMatrix();
	};
}
