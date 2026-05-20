#pragma once
#include <GLFW/glfw3.h>
#include <array>
#include "enemy.hpp"
#include "player.hpp"
#include "spawning.hpp"

bool checkCollisions(Player& player, Enemy& enemy);

class Game
{
	Renderer renderer;
	
	Player player;
	std::array<Enemy, 50> enemies;
	Spawner spawner;

	int lives = 3;
public:
	void Init();
	void Update(GLFWwindow* window, float dt);
	void Draw();

	void DrawLives();
};