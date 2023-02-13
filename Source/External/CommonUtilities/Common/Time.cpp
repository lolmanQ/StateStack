#include "Time.h"

namespace CU
{
	float Time::myTimeScale;

	std::chrono::time_point<std::chrono::high_resolution_clock> Time::myStartPoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> Time::myLastTimePoint;

	float Time::myDeltaTime;
	float Time::myDeltaTimeUnScaled;
	float Time::myTime;
	float Time::myUnScaledTime;

	double Time::myDeltaTimeD;
	double Time::myDeltaTimeDUnScaled;
	double Time::myTimeD;
	double Time::myUnScaledTimeD;

	void Time::Init()
	{
		myStartPoint = std::chrono::high_resolution_clock::now();
		myLastTimePoint = myStartPoint;
		myTimeScale = 1.f;

		myDeltaTime = 0;
		myDeltaTimeUnScaled = 0;
		myTime = 0;
		myUnScaledTime = 0;
		
		myDeltaTimeD = 0;
		myDeltaTimeDUnScaled = 0;
		myTimeD = 0;
		myUnScaledTimeD = 0;
	}

	void Time::Update()
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTimePoint = std::chrono::high_resolution_clock::now();
		myDeltaTimeDUnScaled = std::chrono::duration_cast<std::chrono::duration<double>>(currentTimePoint - myLastTimePoint).count();
		myDeltaTimeUnScaled = static_cast<float>(myDeltaTimeDUnScaled);
		myDeltaTimeD = myDeltaTimeDUnScaled * static_cast<double>(myTimeScale);
		myDeltaTime = static_cast<float>(myDeltaTimeD);
		myLastTimePoint = currentTimePoint;
		myTime += myDeltaTime;
		myTimeD += myDeltaTimeD;
		myUnScaledTime += myDeltaTimeUnScaled;
		myUnScaledTimeD += myDeltaTimeDUnScaled;
	}

	void Time::SetTimeScale(const float& aTimeScale)
	{
		myTimeScale = aTimeScale;
	}

	float Time::GetTimeScale()
	{
		return myTimeScale;
	}

	float Time::GetDeltaTime()
	{
		return myDeltaTime;
	}

	float Time::GetUnScaledDeltaTime()
	{
		return myDeltaTimeUnScaled;
	}

	float Time::GetTime()
	{
		return myTime;
	}

	float Time::GetUnScaledTime()
	{
		return myUnScaledTime;
	}

	double Time::GetDeltaTimeDouble()
	{
		return myDeltaTimeD;
	}

	double Time::GetUnScaledDeltaTimeDouble()
	{
		return myDeltaTimeDUnScaled;
	}

	double Time::GetTimeDouble()
	{
		return myTimeD;
	}

	double Time::GetUnScaledTimeDouble()
	{
		return myUnScaledTimeD;
	}
}

