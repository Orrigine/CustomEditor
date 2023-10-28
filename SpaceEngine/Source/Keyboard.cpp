#include "Headers/Keyboard.h"

std::shared_ptr<Engine::Keyboard> Engine::Keyboard::_instance = nullptr;

int getIndexOfIntVector(std::vector<int> v, int K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found 
	if (it != v.end())
	{

		// calculating the index 
		// of K 
		int index = it - v.begin();
		return index;
	}
	else {
		// If the element is not 
		// present in the vector 
		return -1;
	}
}
int isInIntVector(std::vector<int> v, int K)
{
	if (getIndexOfIntVector(v, K) != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Engine::Keyboard::Keyboard()
{
	_keyPressed = std::vector<int>();
}

Engine::Keyboard::~Keyboard() {}

void Engine::Keyboard::IsPressed(int key)
{
	if (!isInIntVector(_keyPressed, key))
	{
		_keyPressed.push_back(key);

	}

}
void Engine::Keyboard::IsReleased(int key)
{
	if (isInIntVector(_keyPressed, key))
	{
		_keyPressed.erase(_keyPressed.begin() + getIndexOfIntVector(_keyPressed, key));
	}

}
//unsigned char Engine::Keyboard::GetKeyCode() { return _key; }
bool Engine::Keyboard::KeyDown(int keySelected)
{
	return isInIntVector(_keyPressed, keySelected);
}

std::shared_ptr<Engine::Keyboard> Engine::Keyboard::GetInstance()
{
	if (_instance == nullptr)
	{
		std::shared_ptr<Engine::Keyboard> ptr(new Engine::Keyboard);
		_instance = ptr;
	}
	return _instance;
}