#pragma once
#include <renderer.hpp>
#include <GLFW/glfw3.h>


class Player
{
private:
	glm::vec3 pos;
	glm::vec2 size;
	float rotation;
	float speed = 375.0f;
	glm::vec3 color;
public:
	Player();
	~Player();

	void Draw(Renderer* renderer);
	void Move(GLFWwindow* window, float dt);
};