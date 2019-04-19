#include "DXUT.h"
#include "Nuclear.h"


Nuclear::Nuclear()
{
}


Nuclear::~Nuclear()
{
}

void Nuclear::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);

	rigidbody->useGravity = false;
	renderer->SetTexture("NUCLEAR");

	speed = 850.0f;

	realPos = VEC(-renderer->Width(), HALF_Y);

	collider->CreateWithTexture(renderer->pTex, [&](Collider* other) { OnCollision(other); });
}

void Nuclear::Update(float dt)
{
	realPos.x += dt * speed;

	transform->position = realPos + CAMERA.vEye - v3Center;
}

void Nuclear::Render()
{
}

void Nuclear::Destroy()
{
}

void Nuclear::OnCollision(Collider * other)
{
	if (other->CompareTag("ENEMY") ||
		other->CompareTag("MINE") ||
		other->CompareTag("METEOR"))
	{
		if (other->gameObject->life)
			other->gameObject->life->OnAttack(1);

		speed = 350.0f;
	}
}
