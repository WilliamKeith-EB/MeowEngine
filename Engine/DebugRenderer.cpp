#include "pch.h"
#include "DebugRenderer.h"
#include "ColliderComponent.h"
#include <algorithm>

meow::DebugRenderer::DebugRenderer() 
	: m_LineWidth{ 2.0f }
	, m_Color{ 1.0f, 0.0f, 1.0f, 0.8f }
	, m_pColliders{} {

}

void meow::DebugRenderer::AddCollider(ColliderComponent* pCollider) {

#ifdef _DEBUG
	m_pColliders.push_back(pCollider);
#else
	UNREFERENCED_PARAMETER(pCollider);
#endif
}

void meow::DebugRenderer::RemoveCollider(ColliderComponent* pCollider) {

#ifdef _DEBUG
	m_pColliders.erase(std::remove(m_pColliders.begin(), m_pColliders.end(), pCollider), m_pColliders.end());
#else
	UNREFERENCED_PARAMETER(pCollider);
#endif
}

void meow::DebugRenderer::Render() {

#ifdef _DEBUG
	glColor4f(1.0f, 0.0f, 1.0f, 0.8f);

	glm::vec2 pos, dim;
	for (ColliderComponent* pCollider : m_pColliders) {

		pos = pCollider->GetPosition();
		dim = pCollider->GetDimensions();
		glLineWidth(m_LineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(pos.x, pos.y);
			glVertex2f(pos.x + dim.x, pos.y);
			glVertex2f(pos.x + dim.x, pos.y + dim.y);
			glVertex2f(pos.x, pos.y + dim.y);
		}
		glEnd();
	}
#endif
}
