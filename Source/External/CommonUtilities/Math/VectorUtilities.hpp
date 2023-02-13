#pragma once
#include "Vector.hpp"

namespace CU
{
	template<typename T>
	Vector4<T> ToVector4P(const Vector2<T>& aVector)
	{
		return Vector4<T>(aVector.x, aVector.y, T(0), T(1));
	}

	template<typename T>
	Vector4<T> ToVector4P(const Vector3<T>& aVector)
	{
		return Vector4<T>(aVector.x, aVector.y, aVector.z, T(1));
	}
	
	template<typename T>
	Vector4<T> ToVector4P(const Vector4<T>& aVector)
	{
		return Vector4<T>(aVector.x, aVector.y, aVector.z, T(1));
	}
	
	template<typename T>
	Vector4<T> ToVector4V(const Vector2<T>& aVector)
	{
		return Vector4<T>(aVector.x, aVector.y, T(0), T(0));
	}

	template<typename T>
	Vector4<T> ToVector4V(const Vector3<T>& aVector)
	{
		return Vector4<T>(aVector.x, aVector.y, aVector.z, T(0));
	}

	template<typename T>
	Vector4<T> ToVector4V(const Vector4<T>& aVector)
	{
		return Vector4<T>(aVector.x, aVector.y, aVector.z, T(0));
	}
	
	template<typename T>
	Vector3<T> ToVector3(const Vector2<T>& aVector)
	{
		return Vector3<T>(aVector.x, aVector.y, T(0));
	}

	template<typename T>
	Vector3<T> ToVector3(const Vector4<T>& aVector)
	{
		return Vector3<T>(aVector.x, aVector.y, aVector.z);
	}
	
	template<typename T>
	Vector2<T> ToVector2(const Vector3<T>& aVector)
	{
		return Vector2<T>(aVector.x, aVector.y);
	}

	template<typename T>
	Vector2<T> ToVector2(const Vector4<T>& aVector)
	{
		return Vector2<T>(aVector.x, aVector.y);
	}
}

namespace CommonUtilities = CU;