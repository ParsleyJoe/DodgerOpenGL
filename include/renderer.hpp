#pragma once
#include "shader.hpp"
#include <glm/glm.hpp>
#include <string>
#include "texture.hpp"

class Renderer
{
	unsigned int spriteVAO, spriteVBO;
	unsigned int textVAO, textVBO;
	Shader spriteShader;
	Shader textShader;
public:

	Renderer();
	~Renderer();

	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color);
	void RenderText(std::string& text, float x, float y, float scale, glm::vec3 color);
	void Init();
	void InitTextRendering();
};