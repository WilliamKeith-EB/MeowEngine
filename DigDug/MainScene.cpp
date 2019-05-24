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

	auto background = new GameObject();
	background->AddToScene(this);
	Texture2D tex{ "../Data/image.jpg" };
	background->AddComponent(new RenderComponent(tex));
	background->GetComponent<TransformComponent>()->SetRenderDepth(0.8f);

	//background = new GameObject("Background");
	//background->AddToScene(this);
	//Texture2D backgroundTexture{ "../Data/background.jpg" };
	//background->AddComponent(new RenderComponent(backgroundTexture));
	//auto transform = background->GetComponent<TransformComponent>();
	//transform->SetAnchor({ 0, 0 });
	//transform->SetRenderDepth(0.2f);

	//background = new GameObject("Background");
	//background->AddToScene(this);
	//background->AddComponent(new RenderComponent(backgroundTexture));
	//transform = background->GetComponent<TransformComponent>();
	//transform->SetAnchor({ 0, 0 });
	//transform->SetRenderDepth(0.7f);

	//background = new GameObject("Background");
	//background->AddToScene(this);
	//background->AddComponent(new RenderComponent(backgroundTexture));
	//transform = background->GetComponent<TransformComponent>();
	//transform->SetAnchor({ 0, 0 });
	//transform->SetRenderDepth(0.1f);

	//background = new GameObject("Background");
	//background->AddToScene(this);
	//background->AddComponent(new RenderComponent(backgroundTexture));
	//transform = background->GetComponent<TransformComponent>();
	//transform->SetAnchor({ 0, 0 });
	//transform->SetRenderDepth(0.6f);

	//background = new GameObject("Background");
	//background->AddToScene(this);
	//background->AddComponent(new RenderComponent(backgroundTexture));
	//transform = background->GetComponent<TransformComponent>();
	//transform->SetAnchor({ 0, 0 });
	//transform->SetRenderDepth(0.5f);

	//background = new GameObject("Background");
	//background->AddToScene(this);
	//background->AddComponent(new RenderComponent(backgroundTexture));
	//transform = background->GetComponent<TransformComponent>();
	//transform->SetAnchor({ 0, 0 });
	//transform->SetRenderDepth(0.4f);


	/*m_pObject = new GameObject("main object");
	m_pObject->AddToScene(this);
	Texture2D texture{ "../Data/image.jpg" };
	m_pObject->AddComponent(new RenderComponent(texture));
	m_pObject->GetComponent<TransformComponent>()->SetRotation(90);
	m_pObject->GetComponent<TransformComponent>()->SetPosition({ 200, 0 });
	m_pObject->GetComponent<TransformComponent>()->SetAnchor({ 0, 1 });*/
}

void MainScene::Update() {

	m_TimePassed += TIME.GetDeltaT();

	if (m_TimePassed >= 1.0f) {

		m_TimePassed -= 1.0f;
		LOGGER.LogInfo(std::to_string(TIME.GetFPS()));
	}
}
