#include "pch.h"
#include "ConfigLoader.h"
#include "Locator.h"
#include "Logger.h"
#include <sstream>

meow::ConfigLoader::ConfigLoader(const std::string& folder)
	: m_pData{ new ConfigData{} }
	, m_Buffer{}
{
	const int bufferSize{ 100 };
	m_Buffer.resize(bufferSize);
	std::memset(m_Buffer.data(), 0, bufferSize);

	std::string engineFile{ folder + "Engine.ini" };

	LoadConfigData("Window", "Width", "640", engineFile);
	m_pData->window.width = std::stof(m_Buffer.data());

	LoadConfigData("Window", "Height", "480", engineFile);
	m_pData->window.height = std::stof(m_Buffer.data());

	LoadConfigData("Window", "Title", "Programming 4 assignment", engineFile);
	m_pData->window.title = m_Buffer.data();

	LoadConfigData("Window", "UseVSync", "true", engineFile);
	bool b{};
	std::istringstream(m_Buffer.data()) >> std::boolalpha >> b;
	m_pData->window.useVSync = b;

	LoadConfigData("Memory", "FrameAllocSize", "1024", engineFile);
	m_pData->memory.frameAllocSize = std::stoi(m_Buffer.data());

	LoadConfigData("Memory", "MaxNumberOfRenderComponents", "50", engineFile);
	m_pData->memory.maxNumberOfRenderComponents = std::stoi(m_Buffer.data());

	LoadConfigData("Memory", "GameObjectArrayStartSize", "60", engineFile);
	m_pData->memory.gameObjectArrayStartSize = std::stoi(m_Buffer.data());
}

meow::ConfigLoader::~ConfigLoader()
{
}

void meow::ConfigLoader::CreateConfigFile(const std::string& file) {

	auto succes = m_ConfigFiles.emplace(std::make_pair(file, std::unordered_map<std::string, std::string>{}));
	
	if (!succes.second) {

		LOGGER.LogWarning("ConfigFile: " + file + " could not be created, because a file with that name already exists");
		return;
	}
}

void meow::ConfigLoader::LoadConfigData(const std::string& title, const std::string& data, const std::string& defaultValue, const std::string& filePath) {
	
	auto size = GetPrivateProfileString(title.c_str(), data.c_str(), "", m_Buffer.data(), DWORD(m_Buffer.size()), filePath.c_str());

	if (size == 0) {

		// write default value
		WritePrivateProfileString(title.c_str(), data.c_str(), defaultValue.c_str(), filePath.c_str());
		GetPrivateProfileString(title.c_str(), data.c_str(), "", m_Buffer.data(), DWORD(m_Buffer.size()), filePath.c_str());
	}
}



