#include "pch.h"
#include "MainScene.h"
#include "DigDugComponent.h"

MainScene::MainScene()
	: Scene( "Main" )
{
}


MainScene::~MainScene()
{
}

void MainScene::Initialize() {

	using namespace meow;

	auto background = new GameObject("Background");
	background->AddToScene(this);
	background->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("background.jpg")));
	auto transform = background->GetComponent<TransformComponent>();
	transform->SetAnchor({ 0, 0 });
	transform->SetRenderDepth(1.0f);

	auto logo = new GameObject("DAELogo");
	logo->AddToScene(this);
	logo->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("logo.png")));
	transform = logo->GetComponent<TransformComponent>();
	transform->SetAnchor({ 1,1 });
	transform->SetPosition({ CONFIGDATA.window.width - 20.0f, CONFIGDATA.window.height - 20.0f });
	transform->SetRenderDepth(0.9f);

	auto digdug = new GameObject("DigDug");
	digdug->AddToScene(this);
	digdug->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("digdug.png")));
	DigDugComponent* digdugComponent = (DigDugComponent*)digdug->AddComponent(new DigDugComponent());
	transform = digdug->GetComponent<TransformComponent>();
	DEBUGRENDERER.AddCollider((ColliderComponent*)digdug->AddComponent(new ColliderComponent(glm::vec2{ 0,0 }, transform->GetSize(), false, digdugComponent, true)));
	transform->SetScale({ 0.2f, 0.2f });
	transform->SetPosition({ CONFIGDATA.window.width / 2, CONFIGDATA.window.height / 2 });
	transform->SetRenderDepth(0.0f);

	auto rock = new GameObject("Rock");
	rock->AddToScene(this);
	rock->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("rock.png")));
	transform = rock->GetComponent<TransformComponent>();
	DEBUGRENDERER.AddCollider((ColliderComponent*)rock->AddComponent(new ColliderComponent(glm::vec2{ 0, 0 }, transform->GetSize(), false, nullptr, true)));
	transform->SetScale({ 0.6f, 0.6f });
	transform->SetAnchor({ 0, 0.5f });
	transform->SetPosition({ 40.0f, CONFIGDATA.window.height / 2 });
	transform->SetRenderDepth(0.2f);

	m_pAperture = new GameObject("Aperture");
	m_pAperture->AddToScene(this);
	m_pAperture->AddComponent(new RenderComponent(RESOURCEMANAGER.GetTexture("aperture.png")));
	transform = m_pAperture->GetComponent<TransformComponent>();
	transform->SetScale({0.1f, 0.1f});
	transform->SetPosition({ 20.0f + transform->GetSize().x * 0.1f / 2, CONFIGDATA.window.height - 20.0f - transform->GetSize().y * 0.1f / 2});
	transform->SetRenderDepth(0.1f);
}

void MainScene::Update() {
	using namespace meow;

	// rotate the aperture
	m_pAperture->GetComponent<TransformComponent>()->Rotate(-30.0f * TIME.GetDeltaT());

	m_TimePassed += TIME.GetDeltaT();

	if (m_TimePassed >= 3.0f) {

		m_TimePassed -= 3.0f;
		LOGGER.LogInfo(std::to_string(TIME.GetFPS()) + " fps");
	}
}
