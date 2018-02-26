#include "InputManager.hpp"

InputManager::InputManager()
{
	keyW_ = false;
	keyA_ = false;
	keyD_ = false;
}


InputManager::~InputManager()
{
}

bool InputManager::GetKeyW()
{
	return keyW_;
}

bool InputManager::GetKeyA()
{
	return keyA_;
}

bool InputManager::GetKeyD()
{
	return keyD_;
}


void InputManager::SetKeyW(bool newValue)
{
	keyW_ = newValue;
}

void InputManager::SetKeyA(bool newValue)
{
	keyA_ = newValue;
}

void InputManager::SetKeyD(bool newValue)
{
	keyD_ = newValue;
}