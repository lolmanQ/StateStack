#pragma once
#include <tge/math/vector2.h>

class AABBCollider
{
public:
	AABBCollider();
	AABBCollider(float aX, float aY, float aWidth, float aHeight);
	AABBCollider(const Tga::Vector2f& aPosition, const Tga::Vector2f& aSize);
	AABBCollider(const Tga::Vector2f& aPosition, const Tga::Vector2f& aSize, const Tga::Vector2f& aPivot);
	~AABBCollider();

	bool CheckCollision(const AABBCollider& aOtherCollider) const;

	Tga::Vector2f GetPosition() const;
	void SetPosition(const Tga::Vector2f& aPosition);
	
	void SetRect(const Tga::Vector2f& aPosition, const Tga::Vector2f& aSize, const Tga::Vector2f& aPivot);

	void DebugRender();
	
	Tga::Vector2f GetTopLeft() const;
	Tga::Vector2f GetTopRight() const;
	Tga::Vector2f GetBottomLeft() const;
	Tga::Vector2f GetBottomRight() const;

private:
	Tga::Vector2f myPosition;
	Tga::Vector2f mySize;
	Tga::Vector2f myPivot;
};

