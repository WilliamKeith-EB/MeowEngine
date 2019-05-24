#include "pch.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager(const std::string& folder)
	: m_Folder{ folder }
{
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {

		LOGGER.LogError(std::string("Couldnt't initialize support for png images: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG){

		LOGGER.LogError(std::string("Couldn't initialize support for jpg images: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) {

		LOGGER.LogError(std::string("Couldn't initialize support for fonts: ") + SDL_GetError());
	}
}


ResourceManager::~ResourceManager()
{
}
