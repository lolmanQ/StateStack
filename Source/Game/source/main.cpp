#include "stdafx.h"

#include "GameWorld.h"

#include <tge/drawers/SpriteDrawer.h>
#include <tge/graphics/GraphicsEngine.h>
#include <CommonUtilities/Input.h>
#include <CommonUtilities/Common/Time.h>
#include <CommonUtilities/Math/Random.h>

#include "StateStack.h"
#include "StateStackProxy.h"

void Go(void);

int main(const int /*argc*/, const char* /*argc*/[])
{
	Go();
	return 0;
}

void Go()
{
	CU::Input::Init();
	CU::Time::Init();
	CU::Random::Init();

	Tga::LoadSettings(TGE_PROJECT_SETTINGS_FILE);

	Tga::EngineCreateParameters createParameters;
	createParameters.myWinProcCallback = CU::Input::BuiltInWinProc; // [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return WinProc(hWnd, message, wParam, lParam); };

	if (!Tga::Engine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return;
	}
	
	{
		Tga::Engine& engine = *Tga::Engine::GetInstance();
		
		StateStack stateStack;
		StateStackProxy stateStackProxy(stateStack);
		
		stateStackProxy.Init();
		
		stateStack.PushState(StateID::Menu);

		GameWorld gameWorld;
		
		gameWorld.Init(engine);

		//Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
		
		while (engine.BeginFrame() && stateStack.size() > 0) {
			CU::Time::Update();

			bool stateReturnValue = stateStack.GetCurrentState()->Update();

			//gameWorld.Update();

			CU::Input::Update();
			//gameWorld.Render(spriteDrawer);
			
			stateStack.RenderStateAtIndex(stateStack.size() - 1);

			if (stateReturnValue == false)
			{
				stateStack.Pop();
			}
			engine.EndFrame();
		}
	}

	Tga::Engine::Shutdown();
}

/*
LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (CU::Input::HandleEvents(message, wParam, lParam))
		return 0;

	lParam;
	wParam;
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		}
	}

	return 0;
}
*/