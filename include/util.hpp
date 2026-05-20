#pragma once
#include <random>
#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


class Random
{
private:
	static std::mt19937 randomEngine;
public:
	static void Init();
	static int InRange(int min, int max);

};

struct Character
{
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

void InitCharacters(FT_Face& face);

inline std::map<char, Character> characters;