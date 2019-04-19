#include "DXUT.h"
#include "Volcano.h"

#include "Meteor.h"
#include "ScaleEffect.h"

Volcano::Volcano()
{
	tag = "VOLCANO";
}


Volcano::~Volcano()
{
}

void Volcano::Init()
{
	AC(Transform);
	AC(Renderer);

	myState = IDLE;

	stateFunc[IDLE] = &Volcano::IdleUpdate;
	stateFunc[ATTACK] = &Volcano::AttackUpdate;

	renderer->renderType = SCREEN;
	renderer->SetTexture("VOLCANO");
}

void Volcano::Update(float dt)
{
	(this->*stateFunc[myState])(dt);

	transform->position.y = defaultHeight - CAMERA.vEye.y + HALF_Y + 130;
}

void Volcano::Render()
{
}

void Volcano::Destroy()
{
}

void Volcano::AttackUpdate(float dt)
{
	frameSkip += dt;

	if (frameSkip > delay)
	{
		if (attackCount-- > 0)
		{
			frameSkip = 0;
			delay = random(0.3f, 0.9f);

			// ATTACK
			DropMeteor();
		}
		else
		{
			// 10초간 대기 상태
			delay = 10.0f;
			frameSkip = 0;

			myState = IDLE;
			renderer->SetFrame(0, 0, 0);
		}
	}
}

void Volcano::IdleUpdate(float dt)
{
	frameSkip += dt;

	if (frameSkip > delay)
	{
		myState = ATTACK;

		frameSkip = 0;
		delay = 0.33f;

		renderer->SetFrame(0, 4, 0.5);
		attackCount = random(8, 12);

		CAMERA.Shake(3500, 1.2f);

		auto scaleEft = InstanceEx(ScaleEffect)(20);
		scaleEft->Setup(GETTEX("VOLCANO_WARNING"), VEC(HALF_X, 200), VEC(0.2, 0.2), 5, 0, 1.5f);
		scaleEft->renderer->renderType = SCREEN;

		RESOURCE.DuplicatePlay("EXPLODE1");
	}
}

void Volcano::Setup(Vector3 pos)
{
	transform->position = pos;
	defaultHeight = pos.y;

	frameSkip	= 0;
	delay		= 10;
	attackCount = 0;

	myState = IDLE;
}

void Volcano::DropMeteor()
{
	Vector3 p = CAMERA.vEye + Vector3(random<int>(-HALF_X, WIDTH), -HEIGHT, 0);

	Vector3 d = VEC(random<float>(-0.5, 0.5), 0);

	InstanceEx(Meteor)(6)->Setup(p, d, 50);
}
