#include "DXUT.h"
#include "Fluffy.h"


Fluffy::Fluffy()
{
}


Fluffy::~Fluffy()
{
}

void Fluffy::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);
	
	rigidbody->useGravity = false;
}

void Fluffy::Update(float dt)
{
	if (bDown)
	{
		rigidbody->AddForce(0, 10);

		if (transform->position.y > plusY)
			bDown = !bDown;
	}
	else
	{
		rigidbody->AddForce(0, -10);

		if (transform->position.y < minusY)
			bDown = !bDown;
	}
}

void Fluffy::Render()
{
}

void Fluffy::Destroy()
{
}

void Fluffy::Setup(Texture * tex, Vector3 pos, float heightDepth)
{
	transform->position = pos;
	renderer->SetTexture(tex);

	minusY	= pos.y - heightDepth / 2.f;
	plusY	= pos.y + heightDepth / 2.f;
}