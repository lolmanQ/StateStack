#pragma once
#include <cmath>
#include <string>
#include <cassert>

namespace CU
{
	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		static const Vector4<T> ZeroP;
		static const Vector4<T> OneP;
		static const Vector4<T> UpP;
		static const Vector4<T> ForwardP;
		static const Vector4<T> RightP;

		static const Vector4<T> ZeroV;
		static const Vector4<T> OneV;
		static const Vector4<T> UpV;
		static const Vector4<T> ForwardV;
		static const Vector4<T> RightV;

		Vector4<T>();
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);
		Vector4<T>(const std::initializer_list<T>& aList);
		Vector4<T>(const Vector4<T>& aVector) = default;
		Vector4<T>& operator=(const Vector4<T>& aVector3) = default;
		~Vector4<T>() = default;

		//Implicit cast operator to any datatype, return initializer list of x, y, z
		template <class U> operator U() const;

		//Returns the negated vector
		Vector4<T> operator-() const;

		//Returns the squared length of the vector
		T LengthSqr() const;

		//Returns the length of the vector
		T Length() const;

		//Returns a normalized copy of this
		Vector4<T> GetNormalized() const;

		//Normalizes the vector
		void Normalize();

		//Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const;

		//Returns distance between vectors
		T Distance(const Vector4<T>& aVector) const;

		//Returns distance between vectors before square root
		T SqrDistance(const Vector4<T>& aVector) const;

		std::string ToString() const;
	};

	using Vector4f = Vector4<float>;
	
#pragma region Operators

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z, aVector0.w + aVector1.w);
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z, aVector0.w - aVector1.w);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return Vector4<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		T inverse = 1 / aScalar;
		return Vector4<T>(aVector.x * inverse, aVector.y * inverse, aVector.z * inverse, aVector.w * inverse);
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		T inverse = 1 / aScalar;
		aVector.x *= inverse;
		aVector.y *= inverse;
		aVector.z *= inverse;
		aVector.w *= inverse;
	}

	template<class T>
	template<class U>
	inline Vector4<T>::operator U() const
	{
		return { x,y,z,w };
	}

	template<class T>
	inline Vector4<T> Vector4<T>::operator-() const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}

#pragma endregion Operators

#pragma region Constructors
	
	template<class T>
	inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template<class T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW) : x(aX), y(aY), z(aZ), w(aW)
	{}

	template<class T>
	inline Vector4<T>::Vector4(const std::initializer_list<T>&aList)
	{
		assert(aList.size() == 4 && "Initializer list size must be 4 for Vector4");
		
		x = aList.begin()[0];
		y = aList.begin()[1];
		z = aList.begin()[2];
		w = aList.begin()[3];
	}
	
#pragma endregion Constructors
	
#pragma region Member functions

	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		return static_cast<T>(SimplePow(x, T(2)) + SimplePow(y, T(2)) + SimplePow(z, T(2)) + SimplePow(w, T(2)));
	}

	template<class T>
	inline T Vector4<T>::Length() const
	{
		return static_cast<T>(std::sqrt(SimplePow(x, T(2)) + SimplePow(y, T(2)) + SimplePow(z, T(2)) + SimplePow(w, T(2))));
	}

	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		T length = Length();
		assert(length != 0 && "Can't normalize a vector with length 0");

		T lengthInverse = 1 / length;
		return Vector4<T>(x * lengthInverse, y * lengthInverse, z * lengthInverse, w * lengthInverse);
	}

	template<class T>
	inline void Vector4<T>::Normalize()
	{
		T length = Length();
		assert(length != 0 && "Can't normalize a vector with length 0");

		T lengthInverse = 1 / length;

		x *= lengthInverse;
		y *= lengthInverse;
		z *= lengthInverse;
		w *= lengthInverse;
	}

	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y + z * aVector.z + w * aVector.w;
	}
	template<class T>
	inline T Vector4<T>::Distance(const Vector4<T>& aVector) const
	{
		return T(std::sqrt(SimplePow(x - aVector.x, T(2)) + SimplePow(y - aVector.y, T(2)) + SimplePow(z - aVector.z, T(2)) + SimplePow(w - aVector.w, T(2))));
	}
	template<class T>
	inline T Vector4<T>::SqrDistance(const Vector4<T>& aVector) const
	{
		return T(SimplePow(x - aVector.x, T(2)) + SimplePow(y - aVector.y, T(2)) + SimplePow(z - aVector.z, T(2)) + SimplePow(w - aVector.w, T(2)));
	}
	template<class T>
	inline std::string Vector4<T>::ToString() const
	{
		return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
	}

#pragma endregion Member functions
	
#pragma region Static member presets

	// Static presets points
	template<typename T>
	const Vector4<T> Vector4<T>::ZeroP(0, 0, 0, 1);
	template<typename T>
	const Vector4<T> Vector4<T>::OneP(1, 1, 1, 1);
	template<typename T>
	const Vector4<T> Vector4<T>::ForwardP(0, 0, 1, 1);
	template<typename T>
	const Vector4<T> Vector4<T>::RightP(1, 0, 0, 1);
	template<typename T>
	const Vector4<T> Vector4<T>::UpP(0, 1, 0, 1);

	// Static presets vectors
	template<typename T>
	const Vector4<T> Vector4<T>::ZeroV(0, 0, 0, 0);
	template<typename T>
	const Vector4<T> Vector4<T>::OneV(1, 1, 1, 0);
	template<typename T>
	const Vector4<T> Vector4<T>::ForwardV(0, 0, 1, 0);
	template<typename T>
	const Vector4<T> Vector4<T>::RightV(1, 0, 0, 0);
	template<typename T>
	const Vector4<T> Vector4<T>::UpV(0, 1, 0, 0);

#pragma endregion Static member presets

#pragma region Extra functions
	
	template<typename T>
	Vector4<T> MinV(const Vector4<T>& aVector1, const Vector4<T>& aVector2)
	{
		T x = CU::Min(aVector1.x, aVector2.x);
		T y = CU::Min(aVector1.y, aVector2.y);
		T z = CU::Min(aVector1.z, aVector2.z);
		T w = CU::Min(aVector1.w, aVector2.w);
		return Vector4<T>(x, y, z, w);
	}

	template<typename T>
	Vector4<T> MaxV(const Vector4<T>& aVector1, const Vector4<T>& aVector2)
	{
		T x = CU::Max(aVector1.x, aVector2.x);
		T y = CU::Max(aVector1.y, aVector2.y);
		T z = CU::Max(aVector1.z, aVector2.z);
		T w = CU::Max(aVector1.w, aVector2.w);
		return Vector4<T>(x, y, z, w);
	}

	template<typename T>
	Vector4<T> DivComp(const Vector4<T>& aVector1, const Vector4<T>& aVector2)
	{
		T x = aVector1.x / aVector2.x;
		T y = aVector1.y / aVector2.y;
		T z = aVector1.z / aVector2.z;
		T w = aVector1.w / aVector2.w;
		return Vector4<T>(x, y, w);
	}

#pragma endregion Extra functions
	
}

namespace CommonUtilities = CU;