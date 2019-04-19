#pragma once
#include "GameObject.h"
class Nuclear :
	public GameObject
{
public:
	Vector3 realPos = v3Zero;
	float	speed	= 0.0f;
public:
	Nuclear();
	virtual ~Nuclear();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void OnCollision(Collider* other);
};

