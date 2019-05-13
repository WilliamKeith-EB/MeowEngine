#pragma once

class ResourceManager final
{
public:
	ResourceManager(const std::string& folder);
	~ResourceManager();

private:
	std::string m_Folder;
};

