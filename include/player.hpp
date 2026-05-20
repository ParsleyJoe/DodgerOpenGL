#pragma once
#include <renderer.hpp>
#include <GLFW/glfw3.h>

class Enemy;

class Player
{
private:
	glm::vec3 pos;
	glm::vec2 size;
	float rotation;
	float speed = 375.0f;
	glm::vec3 color;

public:
	float invulTimer = 0.0f;
	float invulTime = 1.0f;

	void Init();
	void Draw(Renderer* renderer);
	void Move(GLFWwindow* window, float dt);
	void Die();

	friend bool checkCollisions(Player& player, Enemy& enemy);
};