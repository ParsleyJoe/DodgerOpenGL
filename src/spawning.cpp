#include "spawning.hpp"
#include "util.hpp"
#include <iostream>

void Spawner::SpawnEnemies(float dt, std::array<Enemy, 50>& enemies)
{
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

	auto& enemy = enemies[i];
	enemy.active = true;
	int rand = Random::InRange(0, 700.0f);
	enemy.pos = glm::vec3(static_cast<float>(rand), enemy.pos.y, enemy.pos.z);
}