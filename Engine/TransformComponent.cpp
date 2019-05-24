#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: m_Position{ 0, 0}
	, m_Rotation{ 0}
	, m_Scale{ 1, 1 }
	, m_Anchor{ 0.5f, 0.5f }
	, m_Size{ 1, 1 }
	, m_RenderDepth{ 0 }
	, m_TransformMatrix{ glm::mat4() }
	, m_Dirty{ true } {

}

void TransformComponent::SetPosition(const glm::vec2& newPosition) {

	m_Position = newPosition;
	m_Dirty = true;
}

void TransformComponent::Move(const glm::vec2& displacement) {

	m_Position += displacement;
	m_Dirty = true;
}

void TransformComponent::SetRotation(float newRotation) {

	m_Rotation = newRotation;
	m_Dirty = true;
}

void TransformComponent::Rotate(float addedRotation) {

	m_Rotation += addedRotation;
	m_Dirty = true;
}

void TransformComponent::SetScale(const glm::vec2& newScale) {

	m_Scale = newScale;
	m_Dirty = true;
}

void TransformComponent::Scale(const glm::vec2& addedScale) {

	m_Scale *= addedScale;
	m_Dirty = true;
}

void TransformComponent::SetSize(const glm::vec2& newSize) {

	m_Size = newSize;
	m_Dirty = true;
}

void TransformComponent::SetAnchor(const glm::vec2& newAnchor) {

	m_Anchor = newAnchor;
	m_Dirty = true;
}

void TransformComponent::SetRenderDepth(float renderDepth) {

	m_RenderDepth = renderDepth;
}

const glm::mat4x4& TransformComponent::GetTransformMatrix() {

	if (m_Dirty)
		CalculateTransformMatrix();

	return m_TransformMatrix;
}

void TransformComponent::CalculateTransformMatrix() {

	glm::vec3 anchor{ m_Anchor.x * m_Size.x, m_Anchor.y * m_Size.y, 0 };
	auto matrix = glm::translate(glm::mat4(), glm::vec3(m_Position, 0));
	matrix = glm::rotate(matrix, glm::radians(m_Rotation), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(m_Scale, 1));
	matrix = glm::translate(matrix, -anchor);
	
	m_TransformMatrix = matrix;

	m_Dirty = false;
}