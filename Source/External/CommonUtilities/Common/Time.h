#pragma once
#include <chrono>

namespace CU
{
	class Time
	{
	public:
		static void Init();
		static void Update();
		
		static void SetTimeScale(const float& aTimeScale);
		static float GetTimeScale();

		static float GetDeltaTime();
		static float GetUnScaledDeltaTime();
		
		static float GetTime();
		static float GetUnScaledTime();

		static double GetDeltaTimeDouble();
		static double GetUnScaledDeltaTimeDouble();

		static double GetTimeDouble();
		static double GetUnScaledTimeDouble();

	private:
		
		static float myTimeScale;
		
		static std::chrono::time_point<std::chrono::high_resolution_clock> myStartPoint;
		static std::chrono::time_point<std::chrono::high_resolution_clock> myLastTimePoint;

		static float myDeltaTime;
		static float myDeltaTimeUnScaled;
		static float myTime;
		static float myUnScaledTime;

		static double myDeltaTimeD;
		static double myDeltaTimeDUnScaled;
		static double myTimeD;
		static double myUnScaledTimeD;
	};
}