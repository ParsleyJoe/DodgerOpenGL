#include "resource_manager.hpp"
#include <glad/glad.h>
#include "stb_image.h"

std::map <std::string, Texture2D> ResourceManager::textureMap{};

void ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	Texture2D texture;
	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	texture.Generate(width, height, data);

	// free image data
	stbi_image_free(data);
	textureMap.insert({ name, texture });
}