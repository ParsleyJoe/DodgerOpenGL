#include <player.hpp>
#include "resource_manager.hpp"
#include <imgui.h>

void Player::Draw(Renderer* renderer)
{
	renderer->DrawSprite(ResourceManager::textureMap["pig"], pos, size, rotation, color);
	ImGui::SliderFloat("PlayerSpeed: ", &this->speed, 0.0f, 600.0f);
}

Player::Player()
{
	pos = glm::vec3(400.0f, 500.0f, 0.0f);
	
	size = glm::vec2(ResourceManager::textureMap["pig"].width * 0.3f, ResourceManager::textureMap["pig"].height * 0.3f);
	rotation = 0.0f;
	color = glm::vec3(1.0f);
}

Player::~Player()
{

}

void Player::Move(GLFWwindow* window, float dt)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->pos.x -= speed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->pos.x += speed * dt;
	}
}