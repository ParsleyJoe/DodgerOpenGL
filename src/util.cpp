#include "util.hpp"
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

std::mt19937 Random::randomEngine{};

void Random::Init()
{
	randomEngine.seed(std::random_device()());
}

int Random::InRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomEngine);
}

void InitCharacters(FT_Face& face)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character gylph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Gylph: " << c << std::endl;
			continue;
		}

		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, character));

	}
}