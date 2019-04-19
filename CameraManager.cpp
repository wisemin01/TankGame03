#include "DXUT.h"
#include "CameraManager.h"

#include "GameObject.h"
#include "Transform.h"

CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

void CameraManager::Initialize(Vector3 p)
{
	vEye = p;
	pTarget = nullptr;
	vOffset = v3Zero;

	range = { 0,0,0,0 };
	useRange = false;

	fShakeDelay = 0;
	fShakeFrameSkip = 0;
	fShakePower = 0;

	bShakeEnable = false;
}

void CameraManager::Update(float dt)
{
	fShakeFrameSkip += dt;

	if (bShakeEnable)
	{
		Vector3 shake = VEC(random(-fShakePower, fShakePower),
			random(-fShakePower, fShakePower));

		vEye += shake * dt;

		fShakePower *= 0.99f;

		if (fShakeFrameSkip >= fShakeDelay)
		{
			bShakeEnable	= false;
			fShakeFrameSkip = 0;
		}
	}

	if (pTarget)
	{
		Vector3 vE = pTarget->transform->position + vOffset;

		Lerp(vEye, vE, CAM_SPD * dt);
	}

	if (useRange)
	{
		if (vEye.x + HALF_X > range.right)
		{
			vEye.x = range.right - HALF_X;
		}
		if (vEye.x - HALF_X < range.left)
		{
			vEye.x = range.left + HALF_X;
		}
		if (vEye.y + HALF_Y > range.bottom)
		{
			vEye.y = range.bottom - HALF_Y;
		}
		if (vEye.y - HALF_Y < range.top)
		{
			vEye.y = range.top + HALF_Y;
		}
	}
}

void CameraManager::Shake(float power, float delay)
{
	if (bShakeEnable == false) {
		fShakePower = power;
		fShakeDelay = delay;
		fShakeFrameSkip = 0;
	}
	else
	{
		if (fShakePower * (fShakeDelay - fShakeFrameSkip) < power * delay)
		{
			fShakePower = power;
			fShakeDelay = delay;
			fShakeFrameSkip = 0;
		}
	}

	bShakeEnable = true;
}

Vector3 CameraManager::TranslateToWorld(Vector3 v)
{
	return v + vEye - v3Center;
}

void CameraManager::UseRange(float l, float t, float r, float b)
{
	SetRect(&range, l, t, r, b);
	useRange = true;
}

void CameraManager::UnuseRange()
{
	useRange = false;
}
