#include "stdafx.h"

#include "InGameState.h"
#include "StateStackProxy.h"

#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/graphics/GraphicsEngine.h>

#include <CommonUtilities/Input.h>

void InGameState::Init()
{
	auto& engine = *Tga::Engine::GetInstance();

	mySpriteSharedData.myTexture = engine.GetTextureManager().GetTexture(Tga::Settings::GetAssetW("Sprites/903580.png").c_str());

	mySprite.myColor = Tga::Color(1, 1, 1);
	mySprite.myPivot = { 0.5f, 0.5f };

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f myResolution = { (float)intResolution.x, (float)intResolution.y };
	mySprite.myPosition = myResolution * 0.5f;
	mySprite.mySize = myResolution;
}

bool InGameState::Update()
{
	if (CU::Input::GetKeyDown(CU::Keys::ESCAPE))
	{
		return false;
	}

	if (CU::Input::GetKeyDown(CU::Keys::O))
	{
		myStateStackProxy.PushState(StateID::Options);
	}

	return true;
}

void InGameState::Render()
{
	auto& engine = *Tga::Engine::GetInstance();

	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());

	spriteDrawer.Draw(mySpriteSharedData, mySprite);
}

void InGameState::ExitState()
{}

void InGameState::Deactivate()
{}
