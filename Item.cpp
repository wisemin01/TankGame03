#include "DXUT.h"
#include "Item.h"

#include "Player.h"

Item::Item()
{
	tag = "ITEM";
}


Item::~Item()
{
}

void Item::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	
	rigidbody->mass = 0.7f;

	collider->Create(100, 100, [&](Collider* other) {
		if (other->CompareTag("PLAYER"))
		{
			Player* player = dynamic_cast<Player*>(other->gameObject);
		
			if (player)
			{
				player->UseItem(itemType, delay, 1);
			}
			Kill();
		}
		});
}

void Item::Update(float dt)
{
	if (ON_COLLISION == COLLISION.PixelCollisionCheck(transform->position))
	{
		rigidbody->AddForce(0, -20);
	}

	if (transform->position.y > UNIT_DROP_BOTTOM_LINE)
		Kill();
}

void Item::Render()
{
}

void Item::Destroy()
{
}

void Item::Setup(Vector3 pos)
{
	transform->position = pos;

	itemType = (ITEM_TYPE)random<int>(DOUBLE_JUMP, NUCLEAR);
	renderer->SetTexture("ITEM_INFO", itemType);

	delay = 15.0f;

	if (itemType == SPEED_UP)
		delay = -1;
}
