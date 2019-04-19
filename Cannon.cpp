#include "DXUT.h"
#include "Cannon.h"

#include "Bullet.h"

Cannon::Cannon()
{
	tag = "CANNON";
}


Cannon::~Cannon()
{
}

void Cannon::Init()
{
	AC(Transform);
}

void Cannon::Update(float dt)
{
	D3DXMATRIX matRot;
	Vector3 end;

	D3DXMatrixRotationZ(&matRot, pTargetTransform->rot);
	D3DXVec3TransformCoord(&end, &vOffset, &matRot);

	transform->position = pTargetTransform->position + pTargetTransform->offset + end;
}

void Cannon::Render()
{
}

void Cannon::Destroy()
{
}

void Cannon::SetPlayer(GameObject * player)
{
	pTargetTransform = player->transform;
}

void Cannon::Attack(Vector3 dir, int damage, BULLET_TYPE type, float lifeTime)
{
	Bullet* bullet = InstanceEx(Bullet)(7);
	
	bullet->Setup(type, GETTEX("BULLET_A"),
		transform->position, dir, 120, lifeTime, damage);
	bullet->EarlyAcceleration(dir, 360);
}

