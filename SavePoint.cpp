#include "DXUT.h"
#include "SavePoint.h"

#include "PlayerController.h"

SavePoint::SavePoint()
{
}


SavePoint::~SavePoint()
{
}

void SavePoint::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);

	bPassed = false;

	renderer->SetTexture("SAVE");
	renderer->SetFrame(0, 0, 0);

	collider->CreateWithTexture(renderer->pTex, [&](Collider* other) {OnCollision(other); });
}

void SavePoint::Update(float dt)
{
	if (renderer->curFrame == renderer->maxFrame)
	{
		renderer->SetFrame(4, 4, 0);
	}
}

void SavePoint::Render()
{
}

void SavePoint::Destroy()
{
}

void SavePoint::Setup(Vector3 pos)
{
	constexpr float permitDepth = 15.0f;

	transform->position = pos;
	transform->position.y -= renderer->Height() / 2.f - permitDepth;
}

void SavePoint::OnCollision(Collider * other)
{
	if (other->CompareTag("PLAYER"))
	{
		if (bPassed == false) {

			bPassed = true;
			renderer->SetFrame(0, 4, 0.2f);

			PlayerController::playerRespawn = transform->position;
		}
	}
}

void SavePoint::CreateSavePoints(int startX, int count)
{
	float createWidth = COLLISION.pixelMap.mapWidth - startX;
	float deviceWidth = createWidth / (float)count;

	for (int i = 0; i < count; i++)
	{
		int x = startX + deviceWidth * i;
		int y = UNIT_DROP_BOTTOM_LINE;

		COLLISION_TYPE r = COLLISION.PixelGetHeight(&y, x);

		if (r == COLLISION_TYPE::SUCCESS)
			InstanceEx(SavePoint)(1)->Setup(VEC(x, y));
	}
}
