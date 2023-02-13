#include "StopWatch.h"

CU::StopWatch::StopWatch()
{
	myStartPoint = std::chrono::high_resolution_clock::now();
	myLastTimePoint = myStartPoint;
	myDeltaTime = 0;
	myDeltaTimef = static_cast<float>(myDeltaTime);
}

void CU::StopWatch::Update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTimePoint = std::chrono::high_resolution_clock::now();
	myDeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTimePoint - myLastTimePoint).count();
	myDeltaTimef = static_cast<float>(myDeltaTime);
	myLastTimePoint = currentTimePoint;
}

float CU::StopWatch::GetDeltaTime() const
{
	return myDeltaTimef;
}

double CU::StopWatch::GetDeltaTimeDouble() const
{
	return myDeltaTime;
}

double CU::StopWatch::GetTotalTime() const
{
	double timeSinceStart = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - myStartPoint).count();
	return timeSinceStart;
}
