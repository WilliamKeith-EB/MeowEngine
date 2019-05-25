#pragma once

#define LOGGER meow::Locator::GetLogger()
#define INPUT meow::Locator::GetInputHandler()
#define TIME meow::Locator::GetTime()
#define SCENEMANAGER meow::Locator::GetSceneManager()
#define FRAMEALLOC meow::Locator::GetFrameAllocator()
#define RESOURCEMANAGER meow::Locator::GetResourceManager()
#define CONFIGDATA meow::Locator::GetConfigData()
#define CAMERA meow::Locator::GetCamera()
#define DEBUGRENDERER meow::Locator::GetDebugRenderer()

namespace meow {

	class Time;
	class InputHandler;
	class Logger;
	class SceneManager;
	class StackAllocator;
	class ResourceManager;
	class CameraComponent;
	class DebugRenderer;
	struct ConfigData;

	class Locator final {

	public:

		static Time& GetTime();
		static InputHandler& GetInputHandler();
		static Logger& GetLogger();
		static SceneManager& GetSceneManager();
		static StackAllocator& GetFrameAllocator();
		static ResourceManager& GetResourceManager();
		static ConfigData& GetConfigData();
		static CameraComponent& GetCamera();
		static DebugRenderer& GetDebugRenderer();

		static void Provide(Time* pTime);
		static void Provide(InputHandler* pInputHandler);
		static void Provide(Logger* pLogger);
		static void Provide(SceneManager* pSceneManager);
		static void Provide(StackAllocator* pFrameAllocator);
		static void Provide(ResourceManager* pResourceManager);
		static void Provide(ConfigData* pConfigData);
		static void Provide(CameraComponent* pCameraComponent);
		static void Provide(DebugRenderer* pDebugRenderer);
	private:
		Locator() = default;
		~Locator() = default;

		static InputHandler* m_pInputHandler;
		static Time* m_pTime;
		static Logger* m_pLogger;
		static SceneManager* m_pSceneManager;
		static StackAllocator* m_pFrameAllocator;
		static ResourceManager* m_pResourceManager;
		static ConfigData* m_pConfigData;
		static CameraComponent* m_pCameraComponent;
		static DebugRenderer* m_pDebugRenderer;
	};
}



