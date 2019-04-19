#pragma once
#include "GameObject.h"


class Volcano :
	public GameObject
{
	using VolcanoFunc = void(Volcano::*)(float);
	enum STATE
	{
		IDLE,
		ATTACK
	};

public:
	float	frameSkip		= 0;
	float	delay			= 0;
	int		attackCount		= 0;
	int		defaultHeight	= 0;

	STATE	myState = IDLE;

public:
	VolcanoFunc stateFunc[2];
public:
	Volcano();
	virtual ~Volcano();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void IdleUpdate(float dt);
	void AttackUpdate(float dt);

	void Setup(Vector3 pos);

private:
	void DropMeteor();
};

