#include "pch.h"
#include "ResourceManager.h"
#include <algorithm>


meow::ResourceManager::ResourceManager(const std::string& folder)
	: m_Folder{ folder }
{
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {

		LOGGER.LogError(std::string("Couldn't initialize support for png images: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG){

		LOGGER.LogError(std::string("Couldn't initialize support for jpg images: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) {

		LOGGER.LogError(std::string("Couldn't initialize support for fonts: ") + SDL_GetError());
	}
}

meow::ResourceManager::~ResourceManager() {

	for (auto texturePair : m_Textures) {

		delete texturePair.second;
	}
}

meow::Texture2D* meow::ResourceManager::GetTexture(const std::string& path) {

	auto it = std::find_if(m_Textures.cbegin(), m_Textures.cend(), 
		[&path](const std::pair<std::string, Texture2D*>& pair) {
		if (pair.first == path)
			return true;
		return false;
	});

	if (it != m_Textures.cend())
		return it->second;

	return LoadTexture(path);
}




meow::Texture2D* meow::ResourceManager::LoadTexture(const std::string& path) {

	Texture2D* pTexture = new Texture2D(m_Folder + path);
	m_Textures.emplace(std::make_pair(path, pTexture));
	return pTexture;
}
