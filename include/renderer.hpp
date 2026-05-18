#pragma once
#include <shader.hpp>
#include <glm/glm.hpp>
#include <texture.hpp>

class Renderer
{
	unsigned int VAO, VBO;
	Shader defaultShader;
public:

	Renderer();
	~Renderer();

	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color);
};