#include "pch.h"
#include "Locator.h"

InputHandler* Locator::m_pInputHandler{};
Time* Locator::m_pTime{};
Logger* Locator::m_pLogger{};
SceneManager* Locator::m_pSceneManager{};
StackAllocator* Locator::m_pFrameAllocator{};
ResourceManager* Locator::m_pResourceManager{};

Time& Locator::GetTime() {

	return *m_pTime;
}

InputHandler& Locator::GetInputHandler() {

	assert(m_pInputHandler);
	return *m_pInputHandler;
}

Logger& Locator::GetLogger() {

	assert(m_pLogger);
	return *m_pLogger;
}

SceneManager& Locator::GetSceneManager() {

	assert(m_pSceneManager);
	return *m_pSceneManager;
}

StackAllocator& Locator::GetFrameAllocator()
{
	assert(m_pFrameAllocator);
	return *m_pFrameAllocator;
}

ResourceManager& Locator::GetResourceManager() {

	assert(m_pResourceManager);
	return *m_pResourceManager;
}

void Locator::Provide(Time* pTime) {

	m_pTime = pTime;
}

void Locator::Provide(InputHandler* pInputHandler) {

	m_pInputHandler = pInputHandler;
}

void Locator::Provide(Logger* pLogger) {

	m_pLogger = pLogger;
}

void Locator::Provide(SceneManager* pSceneManager) {

	m_pSceneManager = pSceneManager;
}

void Locator::Provide(StackAllocator* pFrameAllocator) {

	m_pFrameAllocator = pFrameAllocator;
}

void Locator::Provide(ResourceManager* pResourceManager) {

	m_pResourceManager = pResourceManager;
}