#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)

class CameraComponent : public Component
{
public:
	CameraComponent(const glm::vec4& backgroundColor = glm::vec4{ 0,0,0,1 });
	virtual ~CameraComponent() = default;

	void Update() override {}

	void SetBackgroundColor(const glm::vec4& backgroundColor) { m_BackgroundColor = backgroundColor; }
	const glm::vec4& GetBackgroundColor() const { return m_BackgroundColor; }

protected:
	glm::vec4 m_BackgroundColor;

};

