#pragma once
#include <random>

namespace CU
{
	class Random
	{
	public:
		static void Init();
		static void SetSeed(const unsigned int& aSeed);
		
		static int GetRandomInt(const int& aMin = 0, const int& aMax = 1);
		static float GetRandomFloat(const float& aMin = 0.f, const float& aMax = 1.f);
		static double GetRandomDouble(const double& aMin = 0.0, const double& aMax = 1.0);
		static bool GetRandomBool();
		
	private:
		static std::mt19937 myRandomGenerator;
	};
}