#include "DXUT.h"
#include "Enemy.h"

#include "Mine.h"
#include "Bullet.h"
#include "Explode.h"

#include "EnemyController.h"
#include "Item.h"

Enemy::Enemy()
{
	tag = "ENEMY";
	EnemyController::enemyCount++;
}


Enemy::~Enemy()
{
	EnemyController::enemyCount--;
	EnemyController::enemyKillCount++;
}

void Enemy::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	rigidbody->useGravity = false;
	transform->scale = VEC(0.7, 0.7);

	Bind();
}

void Enemy::Update(float dt)
{
	(this->*stateFunc[enemyType][enemyState])(dt);

	if (transform->position.y > CAMERA.vEye.y + offset.y) {

		direction.y = 0;
		rigidbody->AddForce(0, -20, 0);
		rigidbody->velocity.y *= 0.95;
	}
}

void Enemy::Render()
{
}

void Enemy::Destroy()
{
}

void Enemy::Setup(ENEMY_TYPE type, Vector3 startPos, Vector3 offset, float speed)
{
	enemyType = type;
	enemyState = MOVE;

	transform->position = startPos;

	this->offset	= offset;
	this->speed		= speed;

	switch (type)
	{
	case DROP_MINE:
		renderer->SetTexture("DROP_MINE");
		life->Setup(17, [&]() { OnDeath(); });
		collider->Create(0, -160, 150, 140, [&](Collider* other) { OnCollision(other); });
		break;
	case DEFAULT:
		renderer->SetTexture("ENEMY");
		life->Setup(20, [&]() { OnDeath(); });
		collider->Create(210, 310, [&](Collider* other) { OnCollision(other); });
		break;
	}
}

void Enemy::DropMineAttack(float dt)
{
	if (renderer->curFrame == renderer->maxFrame)
	{
		InstanceEx(Mine)(5)->SetupWithDrop(transform->position + VEC(0, 10));
		renderer->SetFrame(0, 0, 0);
		enemyState = MOVE;
	}
	rigidbody->AddForce(direction, speed * 0.33f);
}

void Enemy::DropMineMove(float dt)
{
	Vector3 vEnd = CAMERA.vEye + offset;
	Vector3 vGap = vEnd - transform->position;

	FLOAT length = D3DXVec3Length(&vGap);

	D3DXVec3Normalize(&direction, &vGap);

	rigidbody->AddForce(direction, speed);

	if (length <= permitGap)
	{
		renderer->SetFrame(0, 3, 0.4);
		enemyState = ATTACK;
	}
}

void Enemy::DefaultAttack(float dt)
{
	if (renderer->curFrame == renderer->maxFrame)
	{
		InstanceEx(Bullet)(7)->Setup(BULLET_TYPE::TO_PLAYER, GETTEX("BULLET_C"),
			transform->position + Vector3(0, 50, 0), Vector3(0, 1, 0), 50, 1.0f, 1);
		renderer->SetFrame(0, 0, 0);
		enemyState = MOVE;
	}
	rigidbody->AddForce(direction, speed * 0.33f);
}

void Enemy::DefaultMove(float dt)
{
	Vector3 vEnd = CAMERA.vEye + offset;
	Vector3 vGap = vEnd - transform->position;

	FLOAT length = D3DXVec3Length(&vGap);

	D3DXVec3Normalize(&direction, &vGap);

	rigidbody->AddForce(direction, speed);

	if (length <= permitGap)
	{
		renderer->SetFrame(0, 3, 0.4);
		enemyState = ATTACK;
	}
}

void Enemy::Bind()
{
	stateFunc[DROP_MINE][ATTACK] = &Enemy::DropMineAttack;
	stateFunc[DROP_MINE][MOVE] = &Enemy::DropMineMove;
	stateFunc[DEFAULT][ATTACK] = &Enemy::DefaultAttack;
	stateFunc[DEFAULT][MOVE] = &Enemy::DefaultMove;
}

void Enemy::OnDeath()
{
	InstanceEx(Explode)(10)->Setup(transform->position,
		GETTEX("EXPLODE_B"), 0.15);

	if (random<int>(0, 1))
		InstanceEx(Item)(6)->Setup(transform->position);

	CAMERA.Shake(2000, 0.3f);
	RESOURCE.DuplicatePlay("EXPLODE2");

	Kill();
}

void Enemy::OnCollision(Collider * other)
{
	if (other->CompareTag("ENEMY"))
	{
		Vector3 d = other->gameObject->transform->position - transform->position;
		D3DXVec3Normalize(&d, &d);
		other->gameObject->rigidbody->AddForce(d, 50);
	}
}
