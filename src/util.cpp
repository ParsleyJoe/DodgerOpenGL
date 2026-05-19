#include "util.hpp"

std::mt19937 Random::randomEngine{};

void Random::Init()
{
	randomEngine.seed(std::random_device()());
}

int Random::InRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomEngine);
}