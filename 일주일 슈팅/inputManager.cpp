#include "stdafx.h"
#include "inputManager.h"

HRESULT inputManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}
	return S_OK;
}

bool inputManager::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool inputManager::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}
	return false;
}

bool inputManager::GetKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) _keyUp[key] = true;
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}
	return false;
}
