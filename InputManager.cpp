#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	memset(bCur, 0, sizeof(bCur));
	memset(bOld, 0, sizeof(bOld));
}


InputManager::~InputManager()
{
}

void InputManager::KeyInput(float dt)
{
	for (int i = 0; i < 256; i++)
	{
		bOld[i] = bCur[i];
		bCur[i] = (bool)GetAsyncKeyState(i);
	}
}

bool InputManager::GetDown(int key)
{
	return !bOld[key] && bCur[key];
}

bool InputManager::GetPress(int key)
{
	return bOld[key] && bCur[key];
}

bool InputManager::GetUp(int key)
{
	return bOld[key] && !bCur[key];
}

Vector3 InputManager::GetMouse()
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	return Vector3(pt.x, pt.y, 0);
}
