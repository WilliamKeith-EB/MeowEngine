#include "pch.h"
#include "Locator.h"

meow::InputHandler* meow::Locator::m_pInputHandler{};
meow::Time* meow::Locator::m_pTime{};
meow::Logger* meow::Locator::m_pLogger{};
meow::SceneManager* meow::Locator::m_pSceneManager{};
meow::StackAllocator* meow::Locator::m_pFrameAllocator{};
meow::ResourceManager* meow::Locator::m_pResourceManager{};
meow::ConfigData* meow::Locator::m_pConfigData{};
meow::CameraComponent* meow::Locator::m_pCameraComponent{};
meow::DebugRenderer* meow::Locator::m_pDebugRenderer{};

meow::Time& meow::Locator::GetTime() {

	assert(m_pTime);
	return *m_pTime;
}

meow::InputHandler& meow::Locator::GetInputHandler() {

	assert(m_pInputHandler);
	return *m_pInputHandler;
}

meow::Logger& meow::Locator::GetLogger() {

	assert(m_pLogger);
	return *m_pLogger;
}

meow::SceneManager& meow::Locator::GetSceneManager() {

	assert(m_pSceneManager);
	return *m_pSceneManager;
}

meow::StackAllocator& meow::Locator::GetFrameAllocator()
{
	assert(m_pFrameAllocator);
	return *m_pFrameAllocator;
}

meow::ResourceManager& meow::Locator::GetResourceManager() {

	assert(m_pResourceManager);
	return *m_pResourceManager;
}

meow::ConfigData& meow::Locator::GetConfigData() {

	assert(m_pConfigData);
	return *m_pConfigData;
}

meow::CameraComponent& meow::Locator::GetCamera() {

	assert(m_pCameraComponent);
	return *m_pCameraComponent;
}

meow::DebugRenderer& meow::Locator::GetDebugRenderer() {
	
	assert(m_pDebugRenderer);
	return *m_pDebugRenderer;
}

void  meow::Locator::Provide(Time* pTime) {

	m_pTime = pTime;
}

void meow::Locator::Provide(InputHandler* pInputHandler) {

	m_pInputHandler = pInputHandler;
}

void  meow::Locator::Provide(Logger* pLogger) {

	m_pLogger = pLogger;
}

void  meow::Locator::Provide(SceneManager* pSceneManager) {

	m_pSceneManager = pSceneManager;
}

void  meow::Locator::Provide(StackAllocator* pFrameAllocator) {

	m_pFrameAllocator = pFrameAllocator;
}

void meow::Locator::Provide(ResourceManager* pResourceManager) {

	m_pResourceManager = pResourceManager;
}

void  meow::Locator::Provide(ConfigData* pConfigData) {

	m_pConfigData = pConfigData;
}

void meow::Locator::Provide(CameraComponent* pCameraComponent) {

	m_pCameraComponent = pCameraComponent;
}

void meow::Locator::Provide(DebugRenderer* pDebugRenderer) {

	m_pDebugRenderer = pDebugRenderer;
}
