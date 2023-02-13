#pragma once
#include <CommonUtilities/Math/Vector3.hpp>
#include "Plane.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "AABB3D.hpp"

namespace CU
{
	// If the ray is parallel to the plane, aOutIntersectionPoint remains unchanged. 
	// If the ray is in the plane, true is returned, if not, false is returned. 
	// If the ray isn't parallel to the plane, the intersection point is stored in aOutIntersectionPoint and true returned.
	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T tValue = (aPlane.GetDValue() - aPlane.GetNormal().Dot(aRay.GetOrigin())) / aPlane.GetNormal().Dot(aRay.GetDirection());
		Vector3<T> hitPoint = aRay.GetOrigin() + aRay.GetDirection() * tValue;

		if (aPlane.IsInside(hitPoint))
		{
			aOutIntersectionPoint = hitPoint;
			return true;
		}
		return false;
	}
	
	// If the ray intersects the AABB, true is returned, if not, false is returned.
	// A ray in one of the AABB's sides is counted as intersecting it.
	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{

		Vector3<T> rayOrg = aRay.GetOrigin();
		Vector3<T> rayDelta = aRay.GetDirection();

		Vector3<T> min = aAABB.GetMin();
		Vector3<T> max = aAABB.GetMax();

		bool inside = true;

		T xt, xn;
		if (rayOrg.x < min.x)
		{
			xt = min.x - rayOrg.x;
			xt /= rayDelta.x;
			inside = false;
			xn = T(-1.0f);
		}
		else if (rayOrg.x > max.x)
		{
			xt = max.x - rayOrg.x;
			xt /= rayDelta.x;
			inside = false;
			xn = T(1.0f);
		}
		else
		{
			xt = T(-1.0f);
		}

		T yt, yn;
		if (rayOrg.y < min.y)
		{
			yt = min.y - rayOrg.y;
			yt /= rayDelta.y;
			inside = false;
			yn = T(-1.0f);
		}
		else if (rayOrg.y > max.y)
		{
			yt = max.y - rayOrg.y;
			yt /= rayDelta.y;
			inside = false;
			yn = T(1.0f);
		}
		else
		{
			yt = T(-1.0f);
		}

		T zt, zn;
		if (rayOrg.z < min.z)
		{
			zt = min.z - rayOrg.z;
			zt /= rayDelta.z;
			inside = false;
			zn = T(-1.0f);
		}
		else if (rayOrg.z > max.z)
		{
			zt = max.z - rayOrg.z;
			zt /= rayDelta.z;
			inside = false;
			zn = T(1.0f);
		}
		else
		{
			zt = T(-1.0f);
		}

		// Ray origin inside box?
		if (inside)
		{
			return true;
		}

		// Select farthest plane - this is
		// the plane of intersection.
		int which = 0;
		T t = xt;
		if (yt > t)
		{
			which = 1;
			t = yt;
		}
		if (zt > t)
		{
			which = 2;
			t = zt;
		}
		switch (which)
		{

			case 0: // intersect with yz plane
			{
				T y = rayOrg.y + rayDelta.y * t;
				if (y < min.y || y > max.y) return false;
				T z = rayOrg.z + rayDelta.z * t;
				if (z < min.z || z > max.z) return false;

			} break;

			case 1: // intersect with xz plane
			{
				T x = rayOrg.x + rayDelta.x * t;
				if (x < min.x || x > max.x) return false;
				T z = rayOrg.z + rayDelta.z * t;
				if (z < min.z || z > max.z) return false;

			} break;

			case 2: // intersect with xy plane
			{
				T x = rayOrg.x + rayDelta.x * t;
				if (x < min.x || x > max.x) return false;
				T y = rayOrg.y + rayDelta.y * t;
				if (y < min.y || y > max.y) return false;

			} break;
		}

		// Return parametric point of intersection
		return true;
	}
	
	// If the ray intersects the sphere, true is returned, if not, false is returned.
	// A rat intersecting the surface of the sphere is considered as intersecting it.
	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{
		Vector3<T> posDif = aRay.GetOrigin() - aSphere.GetCenter();

		T posDirDot = aRay.GetDirection().Dot(posDif);

		T c = posDif.Dot(posDif) - SimplePow(aSphere.GetRadius(), 2);

		if (c > T(0) && posDirDot > T(0)) return false;
		T discr = SimplePow(posDirDot, 2) - c;

		if (discr < T(0)) return false;

		return true;
	}

}

namespace CommonUtilities = CU;