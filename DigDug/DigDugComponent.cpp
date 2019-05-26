#include "pch.h"
#include "DigDugComponent.h"

void DigDugComponent::Update() {

	using namespace meow;

	auto transform = m_pGameObject->GetComponent<TransformComponent>();
	transform->Move({ -100.0f * TIME.GetDeltaT(), 0.0f });

	if (transform->GetPosition().x < 0)
		transform->SetPosition({ CONFIGDATA.window.width, transform->GetPosition().y });
}

void DigDugComponent::OnCollision() {

	LOGGER.LogInfo("Colliding with the rock");
}
