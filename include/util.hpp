#pragma once
#include <random>

class Random
{
private:
	static std::mt19937 randomEngine;
public:
	static void Init();
	static int InRange(int min, int max);

};