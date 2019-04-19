#pragma once
#include "GameObject.h"
class Cannon :
	public GameObject
{
public:
	Transform * pTargetTransform = nullptr;
	Vector3 vOffset = v3Zero;
public:
	Cannon();
	virtual ~Cannon();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetPlayer(GameObject* player);

	void Attack(Vector3 dir, int damage, BULLET_TYPE type, float lifeTime = 1.0f);
};

