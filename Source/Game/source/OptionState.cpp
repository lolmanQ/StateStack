#include "stdafx.h"

#include "OptionState.h"
#include "StateStackProxy.h"

#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/graphics/GraphicsEngine.h>

#include <CommonUtilities/Input.h>

void OptionState::Init()
{
	auto& engine = *Tga::Engine::GetInstance();

	mySpriteSharedData.myTexture = engine.GetTextureManager().GetTexture(Tga::Settings::GetAssetW("Sprites/1702050-vga_charts_2008_2_9_158193_13.png").c_str());

	mySprite.mySize = mySpriteSharedData.myTexture->CalculateTextureSize();
	mySprite.myColor = Tga::Color(1, 1, 1);
	mySprite.myPivot = { 0.5f, 0.5f };

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f myResolution = { (float)intResolution.x, (float)intResolution.y };
	mySprite.myPosition = myResolution * 0.5f;
}

bool OptionState::Update()
{
	if (CU::Input::GetKeyDown(CU::Keys::ESCAPE))
	{
		return false;
	}

	return true;
}

void OptionState::Render()
{
	auto& engine = *Tga::Engine::GetInstance();

	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());

	spriteDrawer.Draw(mySpriteSharedData, mySprite);
}

void OptionState::ExitState()
{}

void OptionState::Deactivate()
{}
