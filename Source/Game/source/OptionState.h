#pragma once
#include "State.h"

class OptionState :
	public State
{
public:
	using State::State;

	// Inherited via State
	void Init() override;

	bool Update() override;
	void Render() override;

	void ExitState() override;
	void Deactivate() override;

	bool LetThroughRender() override { return true; }
	
private:
	Tga::Sprite2DInstanceData mySprite;
	Tga::SpriteSharedData mySpriteSharedData;
};

