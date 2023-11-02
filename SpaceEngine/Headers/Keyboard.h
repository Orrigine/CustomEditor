
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

	enum class KEYS
	{
		A = 0x41,
		Q = 0x51,
		S = 0x53,
		D = 0x44,
		Z = 0x5A,
		SPACE = 0x20
	};

	int UsedKeys[6] = { 0x41,0x51, 0x53, 0x44,0x5A, 0x20};
	
	//create an instance ?
	class Keyboard
	{
	
	public:
		Keyboard();
		bool Keydown(char); // fonction de check
		void UpdateKeys(); // mettre dans update
		
	private:
		std::map<int, Engine::KeyState> mKeyStates;
	};
}