#pragma once
#include "GameObject.h"


class Bullet :
	public GameObject
{
public:
	using BulletFuntion = void(Bullet::*)(float);

public:
	BulletFuntion	typeFunc	= nullptr;
	BULLET_TYPE		myType		= BULLET_END;
	Vector3			direction	= v3Zero;

	int				damage		= 0;
	float			speed		= 0;
	float			frameSkip	= 0;
	float			delay		= 0;

	float			frameSkip_r = 0;
	float			delay_r		= 0.15f;
public:
	// 추적 총알일 경우에만 사용
	Collider * rangeCollider = nullptr;
	GameObject* targetObject = nullptr;
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void NormalUpdate(float dt);
	void TrackingUpdate(float dt);
	void ToPlayerUpdate(float dt);

	void FuncBind(BULLET_TYPE type);

	void Setup(BULLET_TYPE type, Texture* tex, Vector3 pos, Vector3 dir, float speed, float delay, int damage);
	void EarlyAcceleration(Vector3 dir, float power = 100.0f);

public:
	void OnCollision(Collider* other);
	void OnTrackCollision(Collider* other);

private:
	void OnBulletDeath();
};

