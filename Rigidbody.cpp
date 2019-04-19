#include "DXUT.h"
#include "Rigidbody.h"
#include "GameObject.h"

Vector3 Rigidbody::gravity = Vector3(0, 9.8f, 0);

Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Init()
{
	gameObject->rigidbody = this;
}

void Rigidbody::Update(float dt)
{
	if (useGravity)
		force += gravity * mass;

	velocity += force * dt;
	force = v3Zero;

	GO->transform->position += velocity;

	velocity.x *= damp.x;
	velocity.y *= damp.y;
}

void Rigidbody::Destroy()
{
	if (gameObject->rigidbody == this)
		gameObject->rigidbody = nullptr;
}

void Rigidbody::AddForce(Vector3 force)
{
	Rigidbody::force += force;
}

void Rigidbody::AddForce(float x, float y)
{
	Rigidbody::force += Vector3(x, y, 0);
}

void Rigidbody::AddForce(Vector3 dir, float force)
{
	Rigidbody::force += dir * force;
}

void Rigidbody::AddForce(float x_dir, float y_dir, float force)
{
	Rigidbody::force += Vector3(x_dir, y_dir, 0) * force;
}
