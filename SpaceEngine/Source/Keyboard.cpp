#include "Headers/Keyboard.h"


namespace Engine
{
	Keyboard::Keyboard()
	{
		for (int i = 0; i < sizeof(UsedKeys); i++)
		{
			mKeyStates[UsedKeys[i]] = KeyState::Release;
		}
	}

	void Keyboard::UpdateKeys()
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

	bool Keyboard::Keydown(char vKeyCode)
	{
		return (mKeyStates[vKeyCode] == KeyState::Press);
	}
}