#pragma once
#include <string>

struct ConfigData {

	struct {

		float width, height;
		std::string title;
	} window;

	struct {

		size_t frameAllocSize;
	} memory;
	// run with or without console
};

class ConfigLoader final
{
public:

	ConfigLoader(const std::string& folder);
	~ConfigLoader();

	ConfigData GetConfigData();
private:
	ConfigData* m_pData;
	std::vector<char> m_Buffer;

	void LoadConfigData(const std::string& title, const std::string& data, const std::string& defaultValue, const std::string& filePath);
};

