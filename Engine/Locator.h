#pragma once

#define LOGGER Locator::GetLogger()
#define INPUT Locator::GetInputHandler()
#define TIME Locator::GetTime()
#define SCENEMANAGER Locator::GetSceneManager()
#define FRAMEALLOC Locator::GetFrameAllocator()
#define RESOURCEMANAGER Locator::GetResourceManager()

class Time;
class InputHandler;
class Logger;
class SceneManager;
class StackAllocator;
class ResourceManager;

class Locator final {

public:

	static Time& GetTime();
	static InputHandler& GetInputHandler();
	static Logger& GetLogger();
	static SceneManager& GetSceneManager();
	static StackAllocator& GetFrameAllocator();
	static ResourceManager& GetResourceManager();

	static void Provide(Time* pTime);
	static void Provide(InputHandler* pInputHandler);
	static void Provide(Logger* pLogger);
	static void Provide(SceneManager* pSceneManager);
	static void Provide(StackAllocator* pFrameAllocator);
	static void Provide(ResourceManager* pResourceManager);
private:
	Locator() = default;
	~Locator() = default;

	static InputHandler* m_pInputHandler;
	static Time* m_pTime;
	static Logger* m_pLogger;
	static SceneManager* m_pSceneManager;
	static StackAllocator* m_pFrameAllocator;
	static ResourceManager* m_pResourceManager;
};
