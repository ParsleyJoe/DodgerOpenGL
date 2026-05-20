#include "spawning.hpp"
#include "util.hpp"
#include <iostream>

void Spawner::SpawnEnemies(float dt, std::array<Enemy, 50>& enemies)
{
	EnemyBoundsCheck(enemies);
	if (this->spawnTimer < this->spawnCoolDown)
	{
		spawnTimer += dt;
		return;
	}

	spawnTimer = 0.0f;
	int i = 0;
	for (i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].active)
			break;
	}

	if (i >= enemies.size())
	{
		std::cout << "Spawner::SpawnEnemies() Could not find a inactive enemy" << std::endl;
		return;
	}

	this->ResetEnemy(enemies[i]);
}

void Spawner::EnemyBoundsCheck(std::array<Enemy, 50>& enemies)
{
	for (auto& enemy : enemies)
	{
		if (enemy.active && enemy.pos.y >= SCR_HEIGHT)
		{
			enemy.active = false;
		}
	}
}

void Spawner::ResetEnemy(Enemy& enemy)
{
	enemy.active = true;
	int rand = Random::InRange(0, 700.0f);
	enemy.pos = glm::vec3(static_cast<float>(rand), -50.0f, enemy.pos.z);
}