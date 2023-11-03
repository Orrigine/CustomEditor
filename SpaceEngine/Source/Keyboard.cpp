#include "Headers/Keyboard.h"


namespace Engine
{
	Input::Input()
	{
		for (int i = 0; i < sizeof(UsedKeys); i++)
		{
			mKeyStates[UsedKeys[i]] = KeyState::Release;
		}
	}

	void Input::UpdateKeys()
	{
		for (int i = 0; i < sizeof(UsedKeys); i++)
		{
			if (d3dUtil::IsKeyDown(UsedKeys[i]))
			{
				if (mKeyStates[UsedKeys[i]] == KeyState::Release || mKeyStates[UsedKeys[i]] == KeyState::Invalid)
				{
					mKeyStates[UsedKeys[i]] = KeyState::Press;
				}
				else {
					mKeyStates[UsedKeys[i]] = KeyState::Release;
				}
			}
		
		}
	}

	bool Input::Keydown(char vKeyCode)
	{
		return (mKeyStates[vKeyCode] == KeyState::Press);
	}

	Engine::FLOAT2 Input::GetMousePos(HWND window)
	{
		GetCursorPos(&mPoint);
		ScreenToClient(window, &mPoint);
		Engine::FLOAT2 pos = { mPoint.x, mPoint.y };
		return pos;
	};


	
}