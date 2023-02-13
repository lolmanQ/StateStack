#pragma once
#include <CommonUtilities/Math/Vector3.hpp>

namespace CU
{
	template<class T>
	class AABB3D
	{
	public:

		// Default constructor: there is no AABB, both min and max points are the zero vector.
		AABB3D();

		// Copy constructor.
		AABB3D(const AABB3D<T>& aAABB3D);

		// Constructor taking the positions of the minimum and maximum corners.
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);
		
		~AABB3D() = default;
		
		
		// Init the AABB with the positions of the minimum and maximum corners, same as
		// the constructor above.
		void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);

		
		// Returns whether a point is inside the AABB: it is inside when the point is on any
		// of the AABB's sides or inside of the AABB.
		bool IsInside(const Vector3<T>& aPosition) const;
		
		// Return Min
		const Vector3<T>& GetMin() const;
		
		// Return Max
		const Vector3<T>& GetMax() const;

	private:
		
		Vector3<T> myMin;
		Vector3<T> myMax;
	};

	using AABB3Df = AABB3D<float>;

	template<class T>
	inline AABB3D<T>::AABB3D()
	{
		myMin = Vector3<T>();
		myMax = Vector3<T>();
	}

	template<class T>
	inline AABB3D<T>::AABB3D(const AABB3D<T>&aAABB3D)
	{
		myMin = aAABB3D.myMin;
		myMax = aAABB3D.myMax;
	}

	template<class T>
	inline AABB3D<T>::AABB3D(const Vector3<T>&aMin, const Vector3<T>&aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}
	
	template<class T>
	inline void AABB3D<T>::InitWithMinAndMax(const Vector3<T>&aMin, const Vector3<T>&aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}
	
	
	template<class T>
	inline bool AABB3D<T>::IsInside(const Vector3<T>&aPosition) const
	{
		if (aPosition.x >= myMin.x && aPosition.x <= myMax.x)
		{
			if (aPosition.y >= myMin.y && aPosition.y <= myMax.y)
			{
				if (aPosition.z >= myMin.z && aPosition.z <= myMax.z)
				{
					return true;
				}
			}
		}
		return false;
	}

	template<class T>
	inline const Vector3<T>& AABB3D<T>::GetMin() const
	{
		return myMin;
	}
	
	template<class T>
	inline const Vector3<T>& AABB3D<T>::GetMax() const
	{
		return myMax;
	}
}

namespace CommonUtilities = CU;