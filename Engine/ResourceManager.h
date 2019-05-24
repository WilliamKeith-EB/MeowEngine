#pragma once
#include <unordered_map>

namespace meow {

	class Texture2D;

	class ResourceManager final
	{
	public:
		ResourceManager(const std::string& folder);

		Texture2D* GetTexture(const std::string& path);

		~ResourceManager();

	private:
		std::string m_Folder;
		std::unordered_map<std::string, Texture2D*> m_Textures;

		Texture2D* LoadTexture(const std::string& path);
	};


}