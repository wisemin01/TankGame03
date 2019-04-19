#pragma once
#include "Component.h"
class Life :
	public Component
{
private:
	int curHp = 0;
	int maxHp = 0;

	function<void()> onDeath;
public:
	bool deathCheck = false;
public:
	Life();
	virtual ~Life();

	virtual void Init() override;
	virtual void Destroy() override;

	void OnAttack(int damage);
	void Setup(int hp, function<void()> on_death);
};

