#pragma once
#include <memory>
#include <vector>
#include <unordered_map>>
#include <iterator>

namespace Engine
{
	
	class Keyboard
	{



	public:
		enum Key
		{
			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			h = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A,
			SHIFT = 0x10,
			CTRL = 0x11,
			SPACEBAR = 0x20,
			ENTER = 0xD,
			BACKSPACE = 0x08,
			DOWN = 0x28,
			RIGHT = 0x27,
			LEFT = 0x25,
			UP = 0x26,
		};	

		Keyboard();
		~Keyboard();
		static std::shared_ptr<Engine::Keyboard> GetInstance();
		void IsPressed(int);
		void IsReleased(int);
		bool KeyDown(int);
		//unsigned char GetKeyCode();
	private:
		static std::shared_ptr<Engine::Keyboard> _instance;
		std::vector<int> _keyPressed;
	};
}