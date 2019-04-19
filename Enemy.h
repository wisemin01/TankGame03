#pragma once
#include "GameObject.h"


class Enemy :
	public GameObject
{
	using EnemyFunc = void(Enemy::*)(float);
public:
	EnemyFunc stateFunc[ENEMY_TYPE::ENEMY_END][STATE::STATE_END];

	ENEMY_TYPE	enemyType	= DEFAULT;
	STATE		enemyState	= MOVE;
public:
	Vector3		offset		= v3Zero;
	Vector3		direction	= v3Zero;

	float		speed		= 0.0f;
	float		permitGap	= 70.0f;

public:
	Enemy();
	virtual ~Enemy();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(ENEMY_TYPE type, Vector3 startPos, Vector3 offset, float speed);

private:
	void DropMineAttack(float dt);
	void DropMineMove(float dt);

	void DefaultAttack(float dt);
	void DefaultMove(float dt);

	void Bind();

	void OnDeath();
	void OnCollision(Collider* other);
};

