#include "game.hpp"
#include "resource_manager.hpp"
#include "util.hpp"
#include <iostream>
#include <sstream>

void Game::Init()
{
	ResourceManager::LoadTexture(RESOURCES_PATH"pig.png", true, "pig");
	
	renderer.Init();
	Random::Init();
	player.Init();
}

void Game::Update(GLFWwindow* window, float dt)
{
	spawner.SpawnEnemies(dt, enemies);
	player.Move(window, dt);
	
	for (auto& enemy : enemies)
	{
		enemy.Update(window, dt);

		if (checkCollisions(player, enemy) && enemy.active)
		{
			if (player.invulTimer >= player.invulTime)
			{
				lives--;
				player.Die();
				player.invulTimer = 0.0f;
				std::cout << "Collision Detected\n";
			}
		}
	}
}

void Game::Draw()
{

	player.Draw(&renderer);

	std::stringstream ss;
	ss << "Lives: " << lives;
	std::string result = ss.str();
	renderer.RenderText(result, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	for (auto& enemy : enemies)
	{
		enemy.Draw(&renderer);
	}
}

bool checkCollisions(Player& player, Enemy& enemy)
{
	bool collissionX = player.pos.x + player.size.x >= enemy.pos.x &&
		enemy.pos.x + enemy.size.x >= player.pos.x;
	bool collissionY = player.pos.y + player.size.y >= enemy.pos.y &&
		enemy.pos.y + enemy.size.y >= player.pos.y;

	return collissionX && collissionY;
}