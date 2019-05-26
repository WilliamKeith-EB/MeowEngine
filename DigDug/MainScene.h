#pragma once
#include "Scene.h"

namespace meow {

	class CameraComponent;
	class GameObject;
}

class MainScene final : public meow::Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Initialize() override;
	virtual void Update() override;

private:
	float m_TimePassed;
	meow::GameObject* m_pAperture;
};

