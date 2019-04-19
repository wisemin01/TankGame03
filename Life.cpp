#include "DXUT.h"
#include "Life.h"
#include "GameObject.h"


Life::Life()
{
}


Life::~Life()
{
}

void Life::Init()
{
	gameObject->life = this;
}

void Life::Destroy()
{
	if (gameObject->life == this)
		gameObject->life = nullptr;
}

void Life::OnAttack(int damage)
{
	curHp -= damage;

	if (curHp < 0)
	{
		curHp = 0;
		deathCheck = true;
		onDeath();
	}
}

void Life::Setup(int hp, function<void()> on_death)
{
	maxHp = curHp = hp;
	onDeath = on_death;
}
