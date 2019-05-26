#pragma 
#include "Component.h"
#include "CollisionListener.h"

class DigDugComponent : public meow::Component, public meow::CollisionListener
{
public:
	DigDugComponent() = default;
	~DigDugComponent() = default;

	void Update() override;
	void OnCollision() override;
};

