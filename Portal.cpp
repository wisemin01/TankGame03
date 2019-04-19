#include "DXUT.h"
#include "Portal.h"

#include "Player.h"
#include "Fade.h"
#include "ScaleEffect.h"
#include "PlayerController.h"
#include "Ground.h"

Portal::Portal()
{
}


Portal::~Portal()
{
}

void Portal::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);

	collider->bTrigger = true;

	collider->Create(1000, 720, [&](Collider* other) {
		if (other->CompareTag("PLAYER"))
		{
			if (player == nullptr) {
				player = dynamic_cast<Player*>(other->gameObject);
				player->bPlayerInvinc = true;
				player->bPlayerControll = false;

				PlayerController::stageClear = true;

				auto scaleEft = InstanceEx(ScaleEffect)(20);
				scaleEft->Setup(GETTEX("CLEAR"), VEC(HALF_X, 200), VEC(0.2, 0.2), 5, 0, 2.5f);
				scaleEft->renderer->renderType = SCREEN;
			}
		}
		});

	renderer->SetTexture("PORTAL");
	renderer->SetFrame(0, 2, 0.3);
}

void Portal::Update(float dt)
{
	if (player)
	{
		Vector3 length = transform->position - player->transform->position;
		Vector3 dir;

		D3DXVec3Normalize(&dir, &length);

		player->rigidbody->AddForce(dir, 80);
		player->transform->rot += dt * rotIndex;
		rotIndex += 0.1f;

		if (D3DXVec3Length(&length) < 20)
		{
			Lerp(player->transform->scale, v3Zero, 3.2 * dt);

			if (player->transform->scale.x < 0.1)
			{
				player->bActive = false;

				InstanceEx(Fade)(50)->Setup(0,
					[&]() {
						SCENE.ChangeScene(nextScene); 
					}, 300);
			}
		}
	}
}

void Portal::Render()
{
}

void Portal::Destroy()
{
}

void Portal::Setup(Vector3 position, const string & next_scene_key)
{
	transform->position = position;
	nextScene = next_scene_key;
}
