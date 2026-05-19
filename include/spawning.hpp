#pragma once
#include <array>
#include "enemy.hpp"

class Spawner
{
private:
	float spawnCoolDown = 3.0f;
	float spawnTimer = 0.0f;
public:
	void SpawnEnemies(float dt, std::array<Enemy, 50>& enemies);
};