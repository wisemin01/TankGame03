#include "DXUT.h"
#include "TopCannon.h"

#include "Bullet.h"

TopCannon::TopCannon()
{
	tag = "CANNON";
}


TopCannon::~TopCannon()
{
}

void TopCannon::Init()
{
	AC(Transform);
	AC(Renderer);

	renderer->SetTexture("PLAYER_TOP");
	renderer->SetCenter(Vector3(30, renderer->Height() / 2, 0));
}

void TopCannon::Update(float dt)
{
	transform->position = pTargetTransform->position + pTargetTransform->offset + vOffset;
	transform->scale = pTargetTransform->scale;

	Vector3 vEnd = CAMERA.TranslateToWorld(INPUT.GetMouse());

	vDirection = vEnd - transform->position;
	D3DXVec3Normalize(&vDirection, &vDirection);
	transform->rot = atan2f(vDirection.y, vDirection.x);
}

void TopCannon::Render()
{
}

void TopCannon::Destroy()
{
}

void TopCannon::SetPlayer(GameObject * player)
{
	pTargetTransform = player->transform;
}

void TopCannon::Attack(int damage, BULLET_TYPE type, float lifeTime)
{
	Bullet* bullet = InstanceEx(Bullet)(7);

	D3DXMATRIX mat;
	D3DXMatrixRotationZ(&mat, transform->rot);

	Vector3 startPos = VEC(fCannonLength, 0);
	D3DXVec3TransformCoord(&startPos, &startPos, &mat);

	bullet->Setup(type, GETTEX("BULLET_B"),
		transform->position + startPos, vDirection, 120, lifeTime, damage);
	bullet->EarlyAcceleration(vDirection, 400);
}
