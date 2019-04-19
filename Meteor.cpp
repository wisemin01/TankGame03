#include "DXUT.h"
#include "Meteor.h"

#include "Explode.h"
#include "ScaleEffect.h"

Meteor::Meteor()
{
	tag = "METEOR";
}


Meteor::~Meteor()
{
}

void Meteor::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	renderer->SetTexture("METEOR");
	rigidbody->mass = 2.0f;
	life->Setup(1, [&]() { OnDeath(); });

	collider->Create(115, 100, [&](Collider* other) {OnCollision(other); });

	screenWarning = true;
}

void Meteor::Update(float dt)
{
	if (droping) {
		constexpr float rotSpeed = 10;

		rigidbody->AddForce(direction, speed);
		transform->rot += dt * rotSpeed;

		if (transform->position.y < CAMERA.vEye.y - HALF_Y)
		{
			screenWarning = true;
		}
		else
			screenWarning = false;

		if (ON_COLLISION == COLLISION.PixelCollisionCheck(transform->position))
		{
			droping = false;
			rigidbody->bActive = false;
		}

		if (transform->position.y > UNIT_DROP_BOTTOM_LINE)
			OnDeath();
	}
	else
	{

	}
}

void Meteor::Render()
{
	if (screenWarning)
	{
		Texture* pTex = renderer->pTex->GetImage(1);

		RESOURCE.SetRenderType(SCROLL);

		RESOURCE.SetTransform(Vector3(transform->position.x, CAMERA.vEye.y - HALF_Y, 0), v3Normal, 0);
		RESOURCE.Draw(pTex, VEC(pTex->info.Width / 2, 0), 0xFFFFFFFF);
	}
}

void Meteor::Destroy()
{
}

void Meteor::Setup(Vector3 pos, Vector3 dir, float speed)
{
	transform->position = pos;
	direction			= dir;
	this->speed			= speed;
	droping				= true;
}

void Meteor::OnCollision(Collider * other)
{
	if (other->CompareTag("PLAYER"))
	{
		other->gameObject->life->OnAttack(1);
		OnDeath();
	}
}

void Meteor::OnDeath()
{
	InstanceEx(ScaleEffect)(10)->Setup(GETTEX("SMOKE"), transform->position,
		VEC(0.1, 0.1), 7, transform->rot, 0.5);
	Kill();
}
