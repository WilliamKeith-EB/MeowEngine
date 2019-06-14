#pragma once
#include <string>
#include <unordered_map>

namespace meow {

	class ConfigLoader final
	{
	public:

		ConfigLoader(const std::string& folder);
		~ConfigLoader();

		void CreateConfigFile(const std::string& file);

		template<typename T>
		T GetData(const std::string& file, const std::string& title, const std::string& data, T defaultValue = T());

		template<>
		float GetData<float>(const std::string& file, const std::string& title, const std::string& data, float defaultValue);
	
		template<>
		int GetData<int>(const std::string& file, const std::string& title, const std::string& data, int defaultValue);

		template<>
		bool GetData<bool>(const std::string& file, const std::string& title, const std::string& data, bool defaultValue);

		template<>
		std::string GetData<std::string>(const std::string& file, const std::string& title, const std::string& data, std::string defaultValue);

	protected:
		std::string m_Folder;
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
			m_ConfigFiles;
		std::vector<char> m_Buffer;

		void LoadConfigData(const std::string& title, const std::string& data, const std::string& defaultValue, const std::string& filePath);
	};

	template<typename T>
	T ConfigLoader::GetData(const std::string& file, const std::string& title, const std::string& data, T defaultValue) {

		WritableType* pDefault = static_cast<WritableType*>(&defaultValue);

		LoadConfigData(title, data, pDefault->ToString(), m_Folder + file);
		T t{};
		WritableType* pOut = static_cast<WritableType*>(&t);
		pOut->ParseFromString(m_Buffer.data());
		return *pOut;
	}

	template<>
	float ConfigLoader::GetData<float>(const std::string& file, const std::string& title, const std::string& data, float defaultValue) {

		LoadConfigData(title, data, std::to_string(defaultValue), m_Folder + file);
		return std::stof(m_Buffer.data());
	}

	template<>
	int ConfigLoader::GetData<int>(const std::string& file, const std::string& title, const std::string& data, int defaultValue) {

		LoadConfigData(title, data, std::to_string(defaultValue), m_Folder + file);
		return std::stoi(m_Buffer.data());
	}

	template<>
	bool ConfigLoader::GetData<bool>(const std::string& file, const std::string& title, const std::string& data, bool defaultValue) {

		LoadConfigData(title, data, defaultValue ? "true" : "false", m_Folder + file);
		bool b{};
		std::istringstream(m_Buffer.data()) >> std::boolalpha >> b;
		return b;
	}

	template<>
	std::string ConfigLoader::GetData<std::string>(const std::string& file, const std::string& title, const std::string& data, std::string defaultValue) {

		LoadConfigData(title, data, defaultValue, m_Folder + file);
		return m_Buffer.data();
	}
	
}