#include "DXUT.h"
#include "Bullet.h"

#include "ScaleEffect.h"

Bullet::Bullet()
{
	tag = "BULLET";
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);
	AC(Life);

	life->Setup(1, [&]() { OnBulletDeath(); });

	rigidbody->useGravity = false;
}

void Bullet::Update(float dt)
{
	frameSkip	+= dt;
	frameSkip_r += dt;

	if (frameSkip >= delay)
	{
		OnBulletDeath();
		frameSkip = 0;
	}
	else
		(this->*typeFunc)(dt);

	if (frameSkip_r >= delay_r)
	{
		InstanceEx(ScaleEffect)(7)->Setup(GETTEX("RING_EFT", 0), transform->position,
			VEC(0.2, 0.2), 2, transform->rot, 0.2f);

		frameSkip_r = 0;
	}
}

void Bullet::Render()
{
}

void Bullet::Destroy()
{
}

void Bullet::NormalUpdate(float dt)
{
	rigidbody->AddForce(direction, speed);
}

void Bullet::TrackingUpdate(float dt)
{
	if (targetObject)
	{
		if (targetObject->bLive == false)
		{
			targetObject = nullptr;
		}
		else
		{
			direction = targetObject->transform->position - transform->position;
			D3DXVec3Normalize(&direction, &direction);
		}
	}

	transform->rot = atan2f(direction.y, direction.x);
	rigidbody->AddForce(direction, speed);
}

void Bullet::ToPlayerUpdate(float dt)
{
	rigidbody->AddForce(direction, speed);
}

void Bullet::FuncBind(BULLET_TYPE type)
{
	switch (myType)
	{
	case NORMAL:
		typeFunc = &Bullet::NormalUpdate;
		break;
	case TRACKING:
		typeFunc = &Bullet::TrackingUpdate;
		break;
	case TO_PLAYER:
		typeFunc = &Bullet::ToPlayerUpdate;
		break;
	default:	
		typeFunc = nullptr;
		break;
	}
}

void Bullet::Setup(BULLET_TYPE type, Texture * tex, Vector3 pos, Vector3 dir, float speed, float delay, int damage)
{
	myType = type;
	transform->position = pos;
	transform->rot = (float)atan2f(dir.y, dir.x);

	this->direction = dir;
	this->damage	= damage;
	this->speed		= speed;
	this->delay		= delay;
	this->frameSkip = 0;

	frameSkip_r		= 0;
	delay_r			= 0.15f;

	renderer->SetTexture(tex);
	FuncBind(type);

	if (type == TRACKING) {
		rangeCollider = AC(Collider);
		rangeCollider->bTrigger = true;
		rangeCollider->Create(WIDTH, HEIGHT, [&](Collider*other) {OnTrackCollision(other); });
		
		AC(Collider)->CreateWithTexture(tex, [&](Collider* other) {OnCollision(other); });
	}
	else
	{
		AC(Collider)->CreateWithTexture(tex, [&](Collider* other) {OnCollision(other); });
	}
}

void Bullet::EarlyAcceleration(Vector3 dir, float power)
{
	rigidbody->AddForce(dir, power);
}

void Bullet::OnCollision(Collider * other)
{
	switch (myType)
	{
	case NORMAL:
		if (other->CompareTag("ENEMY") || other->CompareTag("MINE") || other->CompareTag("METEOR"))
		{
			other->gameObject->life->OnAttack(damage);
			OnBulletDeath();
		}
		break;
	case TRACKING:
		if (other->CompareTag("ENEMY") || other->CompareTag("MINE") || other->CompareTag("METEOR"))
		{
			other->gameObject->life->OnAttack(damage);
			OnBulletDeath();
		}
		break;
	case TO_PLAYER:
		if (other->CompareTag("PLAYER"))
		{
			other->gameObject->life->OnAttack(damage);
			OnBulletDeath();
		}
		break;
	case BULLET_END:
		break;
	}
}

void Bullet::OnTrackCollision(Collider * other)
{
	if (other->CompareTag("ENEMY") || other->CompareTag("MINE") || other->CompareTag("METEOR"))
	{
		if (targetObject == nullptr)
		{
			if (other->gameObject->bLive == true)
				targetObject = other->gameObject;
		}
	}
}

void Bullet::OnBulletDeath()
{
	Kill();
}
