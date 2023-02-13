#pragma once
#include <chrono>

namespace CU
{
	class StopWatch
	{
	public:
		StopWatch();
		StopWatch(const StopWatch& aTimer) = delete;
		StopWatch& operator=(const StopWatch& aStopWatch) = delete;
		void Update();
		float GetDeltaTime() const;
		double GetDeltaTimeDouble() const;
		double GetTotalTime() const;

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> myStartPoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> myLastTimePoint;

		double myDeltaTime;
		float myDeltaTimef;
	};
}
