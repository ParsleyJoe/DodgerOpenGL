#pragma once
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include <renderer.hpp>

class Player;

class Enemy
{
private:
	glm::vec3 pos;
	glm::vec2 size;
	float rotation = 0.0f;
	float speed = 400.0f;
	glm::vec3 color;

public:
	bool active = false;
	friend class Spawner;

	Enemy();
	
	void Draw(Renderer* renderer);
	void Update(GLFWwindow* window, float dt);

	friend bool checkCollisions(Player& player, Enemy& enemy);
};