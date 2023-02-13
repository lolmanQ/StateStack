#include "Random.h"

std::mt19937 CU::Random::myRandomGenerator;

void CU::Random::Init()
{
	myRandomGenerator = std::mt19937(std::random_device()());
}

void CU::Random::SetSeed(const unsigned int& aSeed)
{
	myRandomGenerator.seed(aSeed);
}

int CU::Random::GetRandomInt(const int& aMin, const int& aMax)
{
	std::uniform_int_distribution randomDistribution(aMin, aMax);
	return randomDistribution(myRandomGenerator);
}

float CU::Random::GetRandomFloat(const float& aMin, const float& aMax)
{
	std::uniform_real_distribution<float> randomDistribution(aMin, aMax);
	return randomDistribution(myRandomGenerator);
}

double CU::Random::GetRandomDouble(const double& aMin, const double& aMax)
{
	std::uniform_real_distribution randomDistribution(aMin, aMax);
	return randomDistribution(myRandomGenerator);
}

bool CU::Random::GetRandomBool()
{
	std::bernoulli_distribution randomDistribution;
	return randomDistribution(myRandomGenerator);
}

