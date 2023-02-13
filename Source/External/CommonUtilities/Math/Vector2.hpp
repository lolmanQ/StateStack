#pragma once
#include <cmath>
#include <string>
#include <cassert>

namespace CU
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2<T>();
		Vector2<T>(const T& aX, const T& aY);
		Vector2<T>(const Vector2<T>& aVector) = default;
		Vector2<T>& operator=(const Vector2<T>& aVector3) = default;
		~Vector2<T>() = default;

		//Implicit cast operator to any datatype, return initializer list of x, y, z
		template <class U> operator U() const;

		//Returns the negated vector
		Vector2<T> operator-() const;

		//Returns the squared length of the vector
		T LengthSqr() const;

		//Returns the length of the vector
		T Length() const;

		//Returns a normalized copy of this
		Vector2<T> GetNormalized() const;

		//Normalizes the vector
		void Normalize();

		//Returns the dot product of this and aVector
		T Dot(const Vector2<T>& aVector) const;

		//Returns distance between vectors
		T Distance(const Vector2<T>& aVector) const;
		
		//Returns distance between vectors before square root
		T SqrDistance(const Vector2<T>& aVector) const;

		std::string ToString() const;
	};

	using Vector2f = Vector2<float>;
	
#pragma region Operators

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y);
	}
	
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y);
	}
	
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar) 
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}
	
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}
	
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		T inverse = 1 / aScalar;
		return Vector2<T>(aVector.x * inverse, aVector.y * inverse);
	}
	
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}
	
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}
	
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}
	
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		T inverse = 1 / aScalar;
		aVector.x *= inverse;
		aVector.y *= inverse;
	}
	
#pragma endregion Operators

#pragma region Constructors

	template<class T>
	inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template<class T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY) : x(aX), y(aY)
	{
	}
	
#pragma endregion Constructors

#pragma region Member functions

	template<class T>
	template<class U>
	inline Vector2<T>::operator U() const
	{
		return { x,y };
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator-() const
	{
		return Vector2<T>(-x, -y);
	}

	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{
		return static_cast<T>(SimplePow(x, T(2)) + SimplePow(y, T(2)));
	}

	template<class T>
	inline T Vector2<T>::Length() const
	{
		return static_cast<T>(std::sqrt(SimplePow(x, T(2)) + SimplePow(y, T(2))));
	}

	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		T length = Length();
		assert(length != 0 && "Can't normalize a vector with length 0");
		
		T lengthInverse = 1 / length;
		return Vector2<T>(x * lengthInverse, y * lengthInverse);
	}

	template<class T>
	inline void Vector2<T>::Normalize()
	{
		T length = Length();
		assert(length != 0 && "Can't normalize a vector with length 0");
		T lengthInverse = 1 / length;

		x *= lengthInverse;
		y *= lengthInverse;
	}

	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y;
	}

	template<class T>
	inline T Vector2<T>::Distance(const Vector2<T>& aVector) const
	{
		return T(std::sqrt(SimplePow(x - aVector.x, T(2)) + SimplePow(y - aVector.y, T(2))));
	}

	template<class T>
	inline T Vector2<T>::SqrDistance(const Vector2<T>& aVector) const
	{
		return T(SimplePow(x - aVector.x, T(2)) + SimplePow(y - aVector.y, T(2)));
	}

	template<class T>
	inline std::string Vector2<T>::ToString() const
	{
		return std::to_string(x) + ", " + std::to_string(y);
	}
	
#pragma endregion Member functions

#pragma region Extra functions

	template<typename T>
	Vector2<T> MinV(const Vector2<T>& aVector1, const Vector2<T>& aVector2)
	{
		T x = CU::Min(aVector1.x, aVector2.x);
		T y = CU::Min(aVector1.y, aVector2.y);
		return Vector2<T>(x, y);
	}

	template<typename T>
	Vector2<T> MaxV(const Vector2<T>& aVector1, const Vector2<T>& aVector2)
	{
		T x = CU::Max(aVector1.x, aVector2.x);
		T y = CU::Max(aVector1.y, aVector2.y);
		return Vector2<T>(x, y);
	}

	template<typename T>
	Vector2<T> DivComp(const Vector2<T>& aVector1, const Vector2<T>& aVector2)
	{
		T x = aVector1.x / aVector2.x;
		T y = aVector1.y / aVector2.y;
		return Vector2<T>(x, y);
	}
#pragma endregion Extra functions
}

namespace CommonUtilities = CU;