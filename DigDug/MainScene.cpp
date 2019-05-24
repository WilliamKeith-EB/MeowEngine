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

	using namespace meow;


	auto background = new GameObject();
	background->AddToScene(this);
	background->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("aperture.png")));
	background->GetComponent<TransformComponent>()->SetRenderDepth(0.6f);
	background->GetComponent<TransformComponent>()->SetPosition({ CONFIGDATA.window.width / 2, CONFIGDATA.window.height / 2 });
	background->GetComponent<TransformComponent>()->SetScale({ 0.7f, 0.7f });

	m_pObject = background;

	m_pCam01 = &CAMERA;
	auto cam02 = new GameObject("Cam02");
	m_pCam02 = (CameraComponent*) cam02->AddComponent(new CameraComponent({ 0,0.5f,0,1 }));
	cam02->AddToScene(this);

	background = new GameObject("Background");
	background->AddToScene(this);
	background->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("background.jpg")));
	auto transform = background->GetComponent<TransformComponent>();
	transform->SetAnchor({ 0, 0 });
	transform->SetRenderDepth(1.0f);

	GameObject* logo = new GameObject("Logo");
	logo->AddToScene(this);
	logo->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("logo.png")));
	logo->GetComponent<TransformComponent>()->SetPosition({ CONFIGDATA.window.width / 2, CONFIGDATA.window.height / 2 });
	logo->GetComponent<TransformComponent>()->SetRenderDepth(0.5f);

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
	using namespace meow;

	CAMERA.GetGameObject()->GetComponent<TransformComponent>()->Rotate(360.0f * TIME.GetDeltaT());
	CAMERA.GetGameObject()->GetComponent<TransformComponent>()->Scale(glm::vec2(1.0f, 1.0f) + 0.5f * TIME.GetDeltaT());

	m_TimePassed += TIME.GetDeltaT();

	if (m_TimePassed >= 1.0f) {

		m_TimePassed -= 1.0f;
		LOGGER.LogInfo(std::to_string(TIME.GetFPS()));
		//LOGGER.LogInfo(std::to_string(INPUT.GetNumberOfConnectedControllers()) + " Controllers connected");
	}
}
