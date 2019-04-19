#pragma once
#include "Singleton.h"
class InputManager :
	public Singleton<InputManager>
{
public:
	bool bCur[256];
	bool bOld[256];
public:
	InputManager();
	virtual ~InputManager();

	void KeyInput(float dt);

	bool GetDown(int key);
	bool GetPress(int key);
	bool GetUp(int key);

	Vector3 GetMouse();
};

#define INPUT InputManager::GetInstance()

#define GetKeyDown INPUT.GetDown
#define GetKeyPress INPUT.GetPress
#define GetKeyUp INPUT.GetUp