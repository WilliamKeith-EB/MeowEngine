#pragma once
#include "Scene.h"

class GameObject;

class MainScene final : public Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Initialize() override;
	virtual void Update() override;

private:
	float m_TimePassed;
	CameraComponent* m_pCam01, *m_pCam02;
};

