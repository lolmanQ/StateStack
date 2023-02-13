#include "Input.h"
#include <iostream>
#include <Windowsx.h>

namespace CU
{
	std::bitset<256> Input::myKeysDown{};
	std::bitset<256> Input::myKeys{};
	std::bitset<256> Input::myKeysPrev{};
	POINT Input::myMousePosition;
	POINT Input::myMousePositionPrev;
	POINT Input::myMouseDelta;
	int Input::myMouseWheelDelta;
	POINT Input::myMouseAbsolutPosition;

	std::string Input::myStringInputBuffer;
	std::string Input::myStringInputBufferPrev;

	void Input::Init()
	{
		for (int i = 0; i < 256; i++)
		{
			myKeys[i] = false;
			myKeysPrev[i] = false;
		}
		myMousePosition = { 0, 0 };
		myMousePositionPrev = { 0, 0 };
		myMouseDelta = { 0, 0 };
		myMouseWheelDelta = 0;
		myMouseAbsolutPosition = { 0, 0 };
	}

	bool Input::HandleEvents(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_KEYDOWN:
		{
			WORD keyFlags = HIWORD(lParam);
			if (!(keyFlags & KF_REPEAT))
			{
				myKeysDown[wParam] = true;
				InternalStringInputHandler(message, wParam, lParam);
			}
			myKeys[wParam] = true;
			break;
		}
		case WM_KEYUP:
			myKeys[wParam] = false;
			break;
		case WM_MOUSEMOVE:
			myMousePosition.x = GET_X_LPARAM(lParam);
			myMousePosition.y = GET_Y_LPARAM(lParam);
			break;
		case WM_LBUTTONDOWN:
			myKeysDown[VK_LBUTTON] = true;
			myKeys[VK_LBUTTON] = true;
			break;
		case WM_LBUTTONUP:
			myKeys[VK_LBUTTON] = false;
			break;
		case WM_RBUTTONDOWN:
			myKeysDown[VK_RBUTTON] = true;
			myKeys[VK_RBUTTON] = true;
			break;
		case WM_RBUTTONUP:
			myKeys[VK_RBUTTON] = false;
			break;
		case WM_MBUTTONDOWN:
			myKeysDown[VK_MBUTTON] = true;
			myKeys[VK_MBUTTON] = true;
			break;
		case WM_MBUTTONUP:
			myKeys[VK_MBUTTON] = false;
			break;
		case WM_MOUSEWHEEL:
			myMouseWheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
			break;
		default:
			return false;
		}
		return true;
	}

	LRESULT Input::BuiltInWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			default:
				break;
		}

		return 0;
	}

	void Input::Update()
	{
		for (int i = 0; i < 256; i++)
		{
			myKeysPrev[i] = myKeys[i];
			myKeysDown[i] = false;
		}
		myMouseWheelDelta = 0;
		myMouseDelta.x = myMousePosition.x - myMousePositionPrev.x;
		myMouseDelta.y = myMousePosition.y - myMousePositionPrev.y;
		myMousePositionPrev = myMousePosition;
		myStringInputBufferPrev = myStringInputBuffer;
		myStringInputBuffer.clear();
	}

	bool Input::GetKeyDown(const int& aKeyCode)
	{
		return myKeysDown[aKeyCode];
	}

	bool Input::GetKeyDown(const Keys& aKeyCode)
	{
		return myKeysDown[static_cast<int>(aKeyCode)];
	}

	bool Input::GetKeyPressed(const int& aKeyCode)
	{
		return myKeys[aKeyCode];
	}

	bool Input::GetKeyPressed(const Keys& aKeyCode)
	{
		return myKeys[static_cast<int>(aKeyCode)];
	}

	bool Input::GetKeyUp(const int& aKeyCode)
	{
		return !myKeys[aKeyCode] && myKeysPrev[aKeyCode];
	}

	bool Input::GetKeyUp(const Keys& key)
	{
		return !myKeys[static_cast<int>(key)] && myKeysPrev[static_cast<int>(key)];
	}

	bool Input::GetMouseButtonDown(const int& aButton)
	{
		return myKeysDown[aButton];
	}

	bool Input::GetMouseButtonDown(const MouseButtons& aButton)
	{
		return myKeysDown[static_cast<int>(aButton)];
	}

	bool Input::GetMouseButtonPressed(const int& aButton)
	{
		return myKeys[aButton];
	}

	bool Input::GetMouseButtonPressed(const MouseButtons& aButton)
	{
		return myKeys[static_cast<int>(aButton)];
	}

	bool Input::GetMouseButtonUp(const int& aButton)
	{
		return !myKeys[aButton] && myKeysPrev[aButton];
	}

	bool Input::GetMouseButtonUp(const MouseButtons& aButton)
	{
		return !myKeys[static_cast<int>(aButton)] && myKeysPrev[static_cast<int>(aButton)];
	}

	POINT Input::GetMousePosition()
	{
		return myMousePosition;
	}

	POINT Input::GetMousePositionDelta()
	{
		return myMouseDelta;
	}

	POINT Input::GetMouseAbsolutePosition()
	{
		GetCursorPos(&myMouseAbsolutPosition);
		return myMouseAbsolutPosition;
	}

	int Input::GetMouseWheelDelta()
	{
		return myMouseWheelDelta;
	}

	void Input::LockMouseToWindow(const bool& aShouldLock, const HWND& aWindowHandle)
	{
		if (aShouldLock)
		{
			RECT rect;
			GetClientRect(aWindowHandle, &rect);

			POINT ul;
			ul.x = rect.left;
			ul.y = rect.top;

			POINT lr;
			lr.x = rect.right;
			lr.y = rect.bottom;
			MapWindowPoints(aWindowHandle, nullptr, &ul, 1);
			MapWindowPoints(aWindowHandle, nullptr, &lr, 1);

			rect.left = ul.x;
			rect.top = ul.y;

			rect.right = lr.x;
			rect.bottom = lr.y;

			ClipCursor(&rect);
		}
		else
		{
			ClipCursor(nullptr);
		}
	}

	void Input::SetMousePosition(const POINT& aPosition)
	{
		SetCursorPos(aPosition.x, aPosition.y);
	}

	std::string Input::GetStringInputBuffer()
	{
		return myStringInputBufferPrev;
	}

	void Input::InternalStringInputHandler(const UINT& aMessage, const WPARAM& aWParam, const LPARAM& aLParam)
	{
		aMessage;
		aLParam;
		//Filter wParams for letters and numbers include space-bar
		if (aWParam >= 0x41 && aWParam <= 0x5A)
		{
			//Check shift
			if (myKeys[VK_SHIFT])
			{
				myStringInputBuffer += static_cast<char>(aWParam);
			}
			else
			{
				myStringInputBuffer += static_cast<char>(aWParam + 0x20);
			}
		}
		else if (aWParam == 0x20)
		{
			myStringInputBuffer += " ";
		}
		else if (aWParam >= 0x30 && aWParam <= 0x40)
		{
			myStringInputBuffer += static_cast<char>(aWParam);
		}
	}

}

