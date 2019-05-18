#include "pch.h"
#include "MainScene.h"

MainScene::MainScene()
	: Scene( "Main" )
{
}


MainScene::~MainScene()
{
}

void MainScene::Initialize() {

	GameObject* obj = new GameObject("main object");
	obj->AddToScene(this);
	obj->AddComponent(new RenderComponent());
	obj->GetComponent<TransformComponent>()->SetRotation(90);
	obj->GetComponent<TransformComponent>()->SetPosition({ 3, 2, 1 });
	obj->GetComponent<TransformComponent>()->SetAnchor({ 2, 1 });
	obj->GetComponent<TransformComponent>()->SetSize({ 2, 1 });
	obj->GetComponent<TransformComponent>()->GetTransformMatrix();
}

void MainScene::Update() {

	Scene::Update();

	m_TimePassed += TIME.GetDeltaT();

	if (m_TimePassed >= 1.0f) {

		m_TimePassed -= 1.0f;
		LOGGER.LogInfo(std::to_string(TIME.GetFPS()));
	}
}
