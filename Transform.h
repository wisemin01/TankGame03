#pragma once
#include "Component.h"
class Transform :
	public Component
{
public:
	Vector3 position	= v3Zero;
	Vector3 scale		= v3Normal;
	Vector3 offset		= v3Zero;

	float rot = 0.0f;
public:
	Transform();
	virtual ~Transform();

	virtual void Init() override;
	virtual void Destroy() override;

	// 현재 transform을 RESOURCE 매니져에 적용합니다.
	void ApplyTransform();
};

