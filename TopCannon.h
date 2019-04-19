#pragma once
#include "GameObject.h"
class TopCannon :
	public GameObject
{
public:
	Transform * pTargetTransform = nullptr;

	Vector3 vOffset			= v3Zero;
	Vector3 vDirection		= v3Zero;

	float	fCannonLength	= 0.0f;
public:
	TopCannon();
	virtual ~TopCannon();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetPlayer(GameObject* player);

	void Attack(int damage, BULLET_TYPE type, float lifeTime = 1.0f);
};

