#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#pragma warning(pop)

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	virtual void Update() override {};
	virtual int GetMemSize() override { return sizeof(TransformComponent); }

	void SetPosition(const glm::vec3& newPosition);
	void Move(const glm::vec3& displacement);
	void SetRotation(float newRotation);
	void Rotate(float addedRotation);
	void SetScale(const glm::vec2& newScale);
	void Scale(const glm::vec2& addedScale);
	void SetSize(const glm::vec2& newSize);
	void SetAnchor(const glm::vec2& newAnchor);

	const glm::vec3& GetPosition() const { return m_Position; }
	float GetRotation() const { return m_Rotation; }
	const glm::vec2& GetScale() const { return m_Scale; }
	const glm::vec2& GetSize() const { return m_Size; }
	const glm::vec2& GetAnchor() const { return m_Anchor; }
	const glm::mat3x3& GetTransformMatrix();
	float GetRenderDepth() const { return m_Position.z; }

private:
	glm::vec3 m_Position;
	float m_Rotation; // rotation in degrees
	glm::vec2 m_Scale;
	glm::vec2 m_Size;
	glm::vec2 m_Anchor; // 0, 0 = bottom left, 1, 1 = top right

	glm::mat3x3 m_TransformMatrix;
	bool m_Dirty;

	void CalculateTransformMatrix();
};

