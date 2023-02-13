#pragma once
#include <cassert>

namespace CU
{
	namespace Math
	{
		constexpr float Pi = 3.14159265358979323846f;
		constexpr float DegToRad = Pi / 180.f;
		constexpr float RadToDeg = 180.f / Pi;
	}

	template<typename T>
	T Max(const T& aFirst, const T& aSecond)
	{
		return aFirst > aSecond ? aFirst : aSecond;
	}
	
	template<typename T>
	T Min(const T& aFirst, const T& aSecond)
	{
		return aFirst < aSecond ? aFirst : aSecond;
	}

	template<typename T>
	T Abs(const T& aValue)
	{
		return aValue < 0 ? -aValue : aValue;
	}

	template<typename T>
	T Floor(const T& aValue)
	{
		return std::floor(aValue);
	}

	template<typename T>
	T Ceil(const T& aValue)
	{
		return std::ceil(aValue);
	}

	template<typename T>
	T Round(const T& aValue)
	{
		return std::round(aValue);
	}
	
	template<typename T>
	T Clamp(const T& aValue, const T& aMin, const T& aMax)
	{
		assert(aMin <= aMax && "Min is bigger than Max");

		return Max(aMin, Min(aMax, aValue));
	}
	
	template<typename T>
	T Lerp(const T& aStart, const T& aEnd, const float& aT)
	{
		return static_cast<T>(aStart + (aEnd - aStart) * aT);
	}
	
	template<typename T>
	void Swap(T& aFirst, T& aSecond)
	{
		T temp = aFirst;
		aFirst = aSecond;
		aSecond = temp;
	}

	template<typename T>
	inline T SimplePow(const T& aValue, const int& aPower)
	{
		T result = 1;
		for (int i = 0; i < aPower; ++i)
		{
			result *= aValue;
		}
		return result;
	}

	// Remap value to new range
	template <typename T>
	T Remap(const T& aValue, const T& aOldMin, const T& aOldMax, const T& aNewMin, const T& aNewMax)
	{
		return (((aValue - aOldMin) * (aNewMax - aNewMin)) / (aOldMax - aOldMin)) + aNewMin;
	}
}

namespace CommonUtilities = CU;