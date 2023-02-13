#pragma once
#include <tge/drawers/SpriteDrawer.h>

class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init(Tga::Engine& aEngine);
	void Update(); 
	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	
private:
};