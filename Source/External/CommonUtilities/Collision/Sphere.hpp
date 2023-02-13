#pragma once
#include <CommonUtilities/Math/Vector3.hpp>
#include <CommonUtilities/Math/Math.hpp>

namespace CU
{
	template<class T>
	class Sphere
	{
	public:
		Sphere();
		Sphere(const Sphere<T>& aSphere);

		// Constructor that takes the center position and radius of the sphere.
		Sphere(const Vector3<T>& aCenter, T aRadius);

		~Sphere() = default;

		// Init the sphere with a center and a radius, the same as the constructor above.
		void InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius);

		// Returns whether a point is inside the sphere: it is inside when the point is on the
		// sphere surface or inside of the sphere.
		bool IsInside(const Vector3<T>& aPosition) const;

		const Vector3<T>& GetCenter() const;

		const T& GetRadius() const;

	private:

		T myRadius;
		Vector3<T> myCenter;

	};

	using Spheref = Sphere<float>;

	template<class T>
	inline Sphere<T>::Sphere()
	{
		myRadius = (T)0;
		myCenter = Vector3<T>();
	}

	template<class T>
	inline Sphere<T>::Sphere(const Sphere<T>&aSphere)
	{
		myRadius = aSphere.myRadius;
		myCenter = aSphere.myCenter;
	}

	template<class T>
	inline Sphere<T>::Sphere(const Vector3<T>&aCenter, T aRadius)
	{
		myRadius = aRadius;
		myCenter = aCenter;
	}


	template<class T>
	inline void Sphere<T>::InitWithCenterAndRadius(const Vector3<T>&aCenter, T aRadius)
	{
		myRadius = aRadius;
		myCenter = aCenter;
	}

	template<class T>
	inline bool Sphere<T>::IsInside(const Vector3<T>&aPosition) const
	{
		T squarePointDistFromCenter = aPosition.SqrDistance(myCenter);
		T squareRadius = SimplePow(myRadius, 2);
		return squareRadius >= squarePointDistFromCenter;
	}
	template<class T>
	inline const Vector3<T>& Sphere<T>::GetCenter() const
	{
		return myCenter;
	}
	template<class T>
	inline const T& Sphere<T>::GetRadius() const
	{
		return myRadius;
	}
}

namespace CommonUtilities = CU;