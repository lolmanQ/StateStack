#include "stdafx.h"

#include "AABBCollider.h"

#include <tge/drawers/DebugDrawer.h>
#include <tge/graphics/GraphicsEngine.h>

AABBCollider::AABBCollider()
{
	
}

AABBCollider::AABBCollider(float aX, float aY, float aWidth, float aHeight)
{
	myPosition = Tga::Vector2f(aX, aY);
	mySize = Tga::Vector2f(aWidth, aHeight);
}

AABBCollider::AABBCollider(const Tga::Vector2f& aPosition, const Tga::Vector2f& aSize)
{
	myPosition = aPosition;
	mySize = aSize;
}

AABBCollider::AABBCollider(const Tga::Vector2f& aPosition, const Tga::Vector2f& aSize, const Tga::Vector2f& aPivot)
{
	myPosition = aPosition;
	mySize = aSize;
	myPivot = aPivot;
}

AABBCollider::~AABBCollider()
{
}

bool AABBCollider::CheckCollision(const AABBCollider& aOtherCollider) const
{
	if ((myPosition.x - myPivot.x * mySize.x) + mySize.x >= aOtherCollider.myPosition.x - aOtherCollider.myPivot.x * aOtherCollider.mySize.x
		&& (myPosition.x - myPivot.x * mySize.x) <= (aOtherCollider.myPosition.x - aOtherCollider.myPivot.x * aOtherCollider.mySize.x) + aOtherCollider.mySize.x
		&& (myPosition.y - myPivot.y * mySize.y) + mySize.y >= aOtherCollider.myPosition.y - aOtherCollider.myPivot.y * aOtherCollider.mySize.y
		&& (myPosition.y - myPivot.y * mySize.y) <= (aOtherCollider.myPosition.y - aOtherCollider.myPivot.y * aOtherCollider.mySize.y) + aOtherCollider.mySize.y)
	{
		return true;
	}
	return false;
}

Tga::Vector2f AABBCollider::GetPosition() const
{
	return myPosition;
}

void AABBCollider::SetPosition(const Tga::Vector2f& aPosition)
{
	myPosition = aPosition;
}

void AABBCollider::SetRect(const Tga::Vector2f& aPosition, const Tga::Vector2f& aSize, const Tga::Vector2f& aPivot)
{	
	myPosition = aPosition;
	mySize = aSize;
	myPivot = aPivot;
}

void AABBCollider::DebugRender()
{
#ifndef _RETAIL
	{
		
		auto& engine = *Tga::Engine::GetInstance();
		Tga::DebugDrawer& dbg = engine.GetDebugDrawer();
		Tga::Color c1 = Tga::Color(0.0f, 1.0f, 0.0f, 1.0f);
		Tga::Color c2 = Tga::Color(1.0f, 0.0f, 0.0f, 1.0f);
		dbg.DrawLine(GetTopLeft(), GetTopRight(), c1);
		dbg.DrawLine(GetTopRight(), GetBottomRight(), c1);
		dbg.DrawLine(GetBottomRight(), GetBottomLeft(), c1);
		dbg.DrawLine(GetBottomLeft(), GetTopLeft(), c1);
		dbg.DrawCircle(myPosition, 5.0f, c2);
	}
#endif
}

Tga::Vector2f AABBCollider::GetTopLeft() const
{
	return Tga::Vector2(myPosition.x - myPivot.x * mySize.x, myPosition.y + myPivot.y * mySize.y);
}

Tga::Vector2f AABBCollider::GetTopRight() const
{
	return Tga::Vector2(myPosition.x + (1 - myPivot.x) * mySize.x, myPosition.y + myPivot.y * mySize.y);
}

Tga::Vector2f AABBCollider::GetBottomLeft() const
{
	return Tga::Vector2(myPosition.x - myPivot.x * mySize.x, myPosition.y - (1 - myPivot.y) * mySize.y);
}

Tga::Vector2f AABBCollider::GetBottomRight() const
{
	return Tga::Vector2(myPosition.x + (1 - myPivot.x) * mySize.x, myPosition.y - (1 - myPivot.y) * mySize.y);
}