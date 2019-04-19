#pragma once
#include "Singleton.h"

class GameObject;
class CameraManager :
	public Singleton<CameraManager>
{
public:
	Vector3 vEye = v3Zero;
	Vector3 vOffset = v3Zero;

	GameObject* pTarget = nullptr;

	RECT range = { 0,0,0,0 };
	bool useRange = false;

	float fShakeDelay		= 0;
	float fShakeFrameSkip	= 0;
	float fShakePower		= 0;

	bool  bShakeEnable = false;
public:
	CameraManager();
	virtual ~CameraManager();

	void Initialize(Vector3 p = v3Zero);

	void Update(float dt);
	void Shake(float power, float delay);

	Vector3 TranslateToWorld(Vector3 v);
	inline void SetTarget(GameObject* target) { pTarget = target; }

	void UseRange(float l, float t, float r, float b);
	void UnuseRange();
};

#define CAMERA CameraManager::GetInstance()
#define CAM_SPD 50
#define CAM_POS CAMERA.vEye