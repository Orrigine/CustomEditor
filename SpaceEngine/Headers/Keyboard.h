
#pragma once

#include <queue>
#include <bitset>
#include <map>

#include "Common/Headers/d3dUtil.h"

namespace Engine
{
	enum class KeyState
	{
		Press,
		Release,
		Hold,	
		Invalid
	};

	struct FLOAT2
	{
		int x;
		int y;
	};
	enum class KEYS
	{
		A = 0x41,
		Q = 0x51,
		S = 0x53,
		D = 0x44,
		Z = 0x5A,
		SPACE = 0x20,
		LEFTMOUSE = 0x01,
		RIGHTMOUSE = 0x02,
	};

	int UsedKeys[8] = { 0x41,0x51, 0x53, 0x44,0x5A, 0x20, 0x01, 0x02};
	
	//create an instance ?
	class Input
	{
	
	public:

		Input();
		Engine::FLOAT2 GetMousePos(HWND window);
		bool Keydown(char); // fonction de check
		void UpdateKeys(); // mettre dans update

		
		
	private:
		POINT mPoint;
		std::map<int, Engine::KeyState> mKeyStates;
	};
}