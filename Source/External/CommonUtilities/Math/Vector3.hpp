#pragma once
#include <cmath>
#include <string>
#include <cassert>
#include "Math.hpp"

namespace CU
{
	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		
		static const Vector3<T> Zero;
		static const Vector3<T> One;
		static const Vector3<T> Up;
		static const Vector3<T> Forward;
		static const Vector3<T> Right;

		// Default constructor, initializes the vector to (0, 0, 0)
		Vector3<T>();
		
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
		Vector3<T>(const std::initializer_list<T>& aList);
		Vector3<T>(const Vector3<T>& aVector) = default;
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
		~Vector3<T>() = default;
		
		//Implicit cast operator to any datatype, return initializer list of x, y, z
		template <class U> operator U() const;

		//Returns the negated vector
		Vector3<T> operator-() const;

		//Returns the squared length of the vector
		T LengthSqr() const;

		//Returns the length of the vector
		T Length() const;

		//Returns a normalized copy of this
		Vector3<T> GetNormalized() const;

		//Normalizes the vector
		void Normalize();

		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;

		//Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const;

		//Returns distance between vectors
		T Distance(const Vector3<T>& aVector) const;

		//Returns distance between vectors before square root
		T SqrDistance(const Vector3<T>& aVector) const;

		Vector3<T> ComponentDivision(const Vector3<T>& aVector) const;
		
		std::string ToString() const;
	};

	using Vector3f = Vector3<float>;

#pragma region Operators

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z);
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		T inverse = 1 / aScalar;
		return Vector3<T>(aVector.x * inverse, aVector.y * inverse, aVector.z * inverse);
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		T inverse = 1 / aScalar;
		aVector.x *= inverse;
		aVector.y *= inverse;
		aVector.z *= inverse;
	}
	
#pragma endregion Operators

#pragma region Constructors

	template<class T>
	inline Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template<class T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ) : x(aX), y(aY), z(aZ)
	{
	}

	template<class T>
	inline Vector3<T>::Vector3(const std::initializer_list<T>& aList)
	{
		assert(aList.size() == 3 && "Initializer list size must be 3 for Vector3");

		x = aList.begin()[0];
		y = aList.begin()[1];
		z = aList.begin()[2];
	}

#pragma endregion Constructors

#pragma region Member functions
	
	template<class T>
	template<class U>
	inline Vector3<T>::operator U() const
	{
		return { x,y,z };
	}

	template<class T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}

	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{
		return static_cast<T>(SimplePow(x, 2) + SimplePow(y, 2) + SimplePow(z, 2));
	}

	template<class T>
	inline T Vector3<T>::Length() const
	{
		return static_cast<T>(std::sqrt(SimplePow(x, 2) + SimplePow(y, 2) + SimplePow(z, 2)));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		T length = Length();
		assert(length != 0 && "Can't normalize a vector with length 0");

		T lengthInverse = 1 / length;
		return Vector3<T>(x * lengthInverse, y * lengthInverse, z * lengthInverse);
	}

	template<class T>
	inline void Vector3<T>::Normalize()
	{
		T length = Length();
		assert(length != 0 && "Can't normalize a vector with length 0");

		T lengthInverse = 1 / length;

		x *= lengthInverse;
		y *= lengthInverse;
		z *= lengthInverse;
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y + z * aVector.z;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		return Vector3<T>(y*aVector.z - z*aVector.y, z*aVector.x - x*aVector.z, x*aVector.y - y*aVector.x);
	}

	template<class T>
	inline T Vector3<T>::Distance(const Vector3<T>& aVector) const
	{
		return T(std::sqrt(SimplePow(x - aVector.x, 2) + SimplePow(y - aVector.y, 2) + SimplePow(z - aVector.z, 2)));
	}

	template<class T>
	inline T Vector3<T>::SqrDistance(const Vector3<T>& aVector) const
	{
		return T(SimplePow(x - aVector.x, 2) + SimplePow(y - aVector.y, 2) + SimplePow(z - aVector.z, 2));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::ComponentDivision(const Vector3<T>& aVector) const
	{
		return Vector3<T>(x / aVector.x, y / aVector.y, z / aVector.z);
	}

	template<class T>
	inline std::string Vector3<T>::ToString() const
	{
		return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
	}
	
#pragma endregion Member functions

#pragma region Static member presets
	
	template<typename T>
	const Vector3<T> Vector3<T>::Zero(0, 0, 0);
	template<typename T>
	const Vector3<T> Vector3<T>::One(1, 1, 1);
	template<typename T>
	const Vector3<T> Vector3<T>::Forward(0, 0, 1);
	template<typename T>
	const Vector3<T> Vector3<T>::Right(1, 0, 0);
	template<typename T>
	const Vector3<T> Vector3<T>::Up(0, 1, 0);

#pragma endregion Static member presets

#pragma region Extra functions
	
	template<typename T>
	Vector3<T> MinV(const Vector3<T>& aVector1, const Vector3<T>& aVector2)
	{
		T x = CU::Min(aVector1.x, aVector2.x);
		T y = CU::Min(aVector1.y, aVector2.y);
		T z = CU::Min(aVector1.z, aVector2.z);
		return Vector3<T>(x, y, z);
	}

	template<typename T>
	Vector3<T> MaxV(const Vector3<T>& aVector1, const Vector3<T>& aVector2)
	{
		T x = CU::Max(aVector1.x, aVector2.x);
		T y = CU::Max(aVector1.y, aVector2.y);
		T z = CU::Max(aVector1.z, aVector2.z);
		return Vector3<T>(x, y, z);
	}

	template<typename T>
	Vector3<T> DivComp(const Vector3<T>& aVector1, const Vector3<T>& aVector2)
	{
		T x = aVector1.x / aVector2.x;
		T y = aVector1.y / aVector2.y;
		T z = aVector1.z / aVector2.z;
		return Vector3<T>(x, y, z);
	}

#pragma endregion Extra functions
}

namespace CommonUtilities = CU;