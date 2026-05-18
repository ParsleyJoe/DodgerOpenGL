#pragma once
#include <map>
#include <string>
#include "texture.hpp"

class ResourceManager
{
public:
	static std::map<std::string, Texture2D> textureMap;

	static void LoadTexture(const char* file, bool alpha, std::string name);
};