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

	// ���� transform�� RESOURCE �Ŵ����� �����մϴ�.
	void ApplyTransform();
};

