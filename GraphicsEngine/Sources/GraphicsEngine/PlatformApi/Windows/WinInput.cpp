#include "WinInput.h"
#include "GraphicsEngine/Internal/InternalInput.h"
#include <Windowsx.h>

#include <iostream>

#ifdef CAN_USE_DIRECT_X


void WinInput::Init()
{
	// TODO : Task08

}

void WinInput::Clear()
{
	InternalInput::Clear();
}

void WinInput::Dispatch(MSG & msg)
{
	// If a key event
	if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
	{
		// https://msdn.microsoft.com/en-us/library/windows/desktop/gg153546(v=vs.85).aspx

		UINT winEvent = msg.message;
		
		// A key in Windows OS
		WPARAM winKey = msg.wParam;

		// If a key is pressed down
		if (winEvent == WM_KEYDOWN)
		{
			// Process keys: Shift, Control, Alt
			if (winKey >= VK_SHIFT && winKey <= VK_MENU)
			{
				// TODO : Task08
				// Call InternalInput
				//комбинации?
			}
			// Process other keys
			else
			{
				// TODO : Task08
				// Call InternalInput
				InternalInput::SetKeyDown(winKey);
			}
		}

		// If a key is pressed up
		if (winEvent == WM_KEYUP)
		{
			// TODO : Task08
			// Call InternalInput
			InternalInput::SetKeyUp(winKey);
		}
	}

	// If a mouse event
	if (msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST)
	{
		//все события связанные с мышкой
		UINT winEvent = msg.message;


		if (winEvent == WM_MOUSEMOVE)
		{
			LPARAM lParam = msg.lParam;
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			InternalInput::SetMousePosition(xPos, yPos);
		}
		else if (winEvent == WM_LBUTTONDOWN)
		{
			/*LPARAM lParam = msg.lParam;
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			std::cout << xPos << " " << yPos << std::endl;*/
			InternalInput::SetMouseButton(0, true);
		}
		else if (winEvent == WM_MBUTTONDOWN)
		{
			InternalInput::SetMouseButton(1, true);
		}
		else if (winEvent == WM_RBUTTONDOWN)
		{
			InternalInput::SetMouseButton(2, true);
		}

		else if (winEvent == WM_LBUTTONUP)
		{
			InternalInput::SetMouseButton(0, false);
		}
		else if (winEvent == WM_MBUTTONUP)
		{
			InternalInput::SetMouseButton(1, false);
		}
		else if (winEvent == WM_RBUTTONUP)
		{
			InternalInput::SetMouseButton(2, false);
		}
	}
}

#endif
