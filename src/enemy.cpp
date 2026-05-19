#include <enemy.hpp>
#include "util.hpp"
#include "resource_manager.hpp"

Enemy::Enemy()
{	
	pos = glm::vec3(200.0f, -80.0f, 0.0f);
	size = glm::vec2(50.0f, 50.0f);
	color = glm::vec3(1.0f);
}

void Enemy::Draw(Renderer* renderer)
{
	if (!active) return;
	renderer->DrawSprite(ResourceManager::textureMap["pig"], pos, size, rotation, color);
}

void Enemy::Update(GLFWwindow* window, float dt)
{
	if (!active) return;
	pos.y += speed * dt;
}