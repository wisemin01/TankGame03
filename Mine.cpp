#include "DXUT.h"
#include "Mine.h"

#include "Explode.h"
#include "EnemyController.h"

Mine::Mine()
{
	tag = "MINE";
}


Mine::~Mine()
{
}

void Mine::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	life->Setup(1, [&]() { OnDeath(); });

	rigidbody->bActive = false;
	transform->scale = VEC(0.6, 0.6);
	bDroping = false;

	renderer->SetTexture("MINE");

	collider->Create(50, 50, [&](Collider* other) { OnCollision(other); });
}

void Mine::Update(float dt)
{
	if (bDroping)
	{
		if (ON_COLLISION == COLLISION.PixelCollisionCheck(transform->position +
			Vector3(0, -collider->Height() / 2 + permitHeight, 0)))
		{
			SetupWithGround(transform->position);
		}
	}
}

void Mine::Render()
{
}

void Mine::Destroy()
{
}

void Mine::SetupWithGround(Vector3 pos)
{
	bDroping			= false;
	rigidbody->bActive	= false;
	transform->position = pos;

	int height = UNIT_DROP_BOTTOM_LINE;

	COLLISION.PixelGetHeight(&height, pos.x);

	if (height >= UNIT_DROP_BOTTOM_LINE)
		Kill();
	else
		transform->position.y = height
		- renderer->Height() / 2 + permitHeight;
}

void Mine::SetupWithDrop(Vector3 pos)
{
	rigidbody->bActive = true;
	bDroping = true;
	transform->position = pos;
}

void Mine::OnCollision(Collider * other)
{
	if (other->CompareTag("PLAYER"))
	{
		other->gameObject->life->OnAttack(1);
		OnDeath();
	}
}

void Mine::OnDeath()
{
	EnemyController::enemyKillCount++;

	InstanceEx(Explode)(10)->Setup(transform->position,
		GETTEX("EXPLODE_B"), 0.15);

	CAMERA.Shake(2000, 0.3f);
	RESOURCE.DuplicatePlay("EXPLODE3");

	Kill();
}

void Mine::CreateMineOnGround(int startX, int count, int depthMin, int depthMax)
{
	int xIndex = startX;

	for (int i = 0; i < count; i++)
	{
		xIndex += random(depthMin, depthMax);

		InstanceEx(Mine)(5)->SetupWithGround(VEC(xIndex, 0));
	}
}
