#include "DXUT.h"
#include "Player.h"

#include "Cannon.h"
#include "TopCannon.h"
#include "Nuclear.h"
#include "ScaleEffect.h"
#include "Explode.h"

void Player::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);
	AC(Collider);
	AC(Life);

	SetTextureWithState();

	transform->position		= Vector3(100, 300, 0);
	transform->offset		= Vector3(0, -75, 0);
	transform->scale		= Vector3(0.6, 0.6, 0);
	renderer->renderType	= SCROLL;
	rigidbody->mass			= 2.0f;
	bPlayerControll			= true;
	delay_smoke				= 0.08f;

	collider->CreateWithTexture(renderer->pTex, [&](Collider*) {});
	collider->offset		= Vector3(0, -100, 0);

	life->Setup(1, [&]() { OnPlayerDeath(); });

	CreateCannons();
	CreateUI();

	CAMERA.SetTarget(this);
}

void Player::Update(float dt)
{
	JumpProcess				(dt);
	InputProcess			(dt);
	PixelCollisionProcess	(dt);
	AttackProcess			(dt);
	ItemProcess				(dt);
	LifeProcess				(dt);
	EffectProcess			(dt);

	// 치트키 모음
	CheetProcess			(dt);
	// 상태 변경점 반영은 제일 마지막에
	StateProcess			(dt);
}

void Player::Render()
{

}

void Player::Destroy()
{
	if (CAMERA.pTarget == this)
		CAMERA.SetTarget(nullptr);
}

void Player::Upgrade(int up_level)
{
	if (playerLevel < PLAYER_LEVEL::PLAYER_TANK_LV3)
		playerLevel = (PLAYER_LEVEL)(playerLevel + 1);
}

void Player::Degrade(int down_level)
{
	if (playerLevel > PLAYER_LEVEL::PLAYER_TANK_LV1)
		playerLevel = (PLAYER_LEVEL)(playerLevel - 1);
}

void Player::Setup(Vector3 startPos)
{
	transform->position = startPos;
}

void Player::UseItem(ITEM_TYPE type, float delay, int plus_count)
{
	itemInfo[type].delay	= delay;
	itemInfo[type].enable	= true;
	itemInfo[type].count	+= plus_count;
	itemInfo[type].frameSkip = 0;
}

// =========================================================
// PROCESSING FUNC
// =========================================================

void Player::InputProcess(float dt)
{
	if (bPlayerControll == false)
		return;

	float speed		= itemInfo[SPEED_UP].enable ? playerSpeed * 1.5f : playerSpeed;
	Vector3 moveVec = v3Zero;

	if (GetKeyPress('A'))		moveVec += VEC(-speed, 0);
	if (GetKeyPress('D'))		moveVec += VEC(speed, 0);

	if (GetKeyDown(VK_SPACE))
	{
		if (bJumpEnable) {
			rigidbody->AddForce(0, -800);

			if (itemInfo[DOUBLE_JUMP].enable == true)
			{
				bDoubleJumpEnable = true;
			}
		}
		else if(bDoubleJumpEnable == true)
		{
			rigidbody->AddForce(0, -800);
			bDoubleJumpEnable = false;
		}
	}

	CONSOLE_LOG(itemInfo[NUCLEAR].count);
	if (GetKeyDown(VK_TAB))
	{
		if (itemInfo[NUCLEAR].Use())
			InstanceEx(Nuclear)(9);
	}

	rigidbody->AddForce(moveVec);

	if (moveVec != v3Zero) playerState = MOVE;
	else playerState = IDLE;
}

void Player::PixelCollisionProcess(float dt)
{
	float width = 100;

	Vector3 position = transform->position;

	if (COLLISION.PixelCollisionCheck(position) == ON_COLLISION)
	{
		Vector3 normal;

		int pivotHeight;
		COLLISION.PixelGetHeight(&pivotHeight, position.x);

		if (SUCCESS == COLLISION.PixelGetNormalVec(&normal, position, width))
		{
			rigidbody->AddForce(normal, 75);

			if (rigidbody->force.y > 0)
				rigidbody->force.y = 0;

			if (position.y > pivotHeight)
				transform->position.y = pivotHeight;
		}
	}

	float pOut;

	int permit = 50;
	int result = COLLISION.PixelGetHeightDepth(&pOut, transform->position, width, &permit);

	if (result & MOVELOCK_LEFT) {
		if (rigidbody->velocity.x < 0)
			rigidbody->velocity.x = 0;
		rigidbody->AddForce(30, 0);
	}

	if (result & MOVELOCK_RIGHT) {
		if (rigidbody->velocity.x > 0)
			rigidbody->velocity.x = 0;
		rigidbody->AddForce(-30, 0);
	}

	COLLISION.PixelGetLineRot(&transform->rot, position, width, dt * 10);
}

void Player::AttackProcess(float dt)
{
	if (bPlayerControll == false)
		return;

	if (!GetKeyDown(VK_LBUTTON))
		return;

	Vector3		cannonDir	= VEC(1, 0);

	BULLET_TYPE type		= itemInfo[TRACKING_BULLET].enable ? BULLET_TYPE::TRACKING : BULLET_TYPE::NORMAL;
	FLOAT		lifeTime	= itemInfo[RANGE_UP].enable ? 2.0f : 0.5f;

	if (itemInfo[THREE_DIR_BULLET].enable)
	{
		// 3 방향
		pCannon->Attack(cannonDir + VEC(0, -0.2), 1, type, lifeTime);
		pCannon->Attack(cannonDir, 1, type, lifeTime);
		pCannon->Attack(cannonDir + VEC(0, 0.2), 1, type, lifeTime);
	}
	else
	{
		// 앞으로 쏜다.
		pCannon->Attack(cannonDir, 1, type, lifeTime);
	}

	// 위에거
	pTopCannon->Attack(1, type, 2.0f);
}

void Player::ItemProcess(float dt)
{
	for (int i = 0; i < ITEM_TYPE::ITEM_END; i++)
	{
		itemInfo[i].Update(dt);
	}
}

void Player::LifeProcess(float dt)
{
	if (transform->position.y >= 800)
	{
		OnPlayerDeath();
	}
}

void Player::JumpProcess(float dt)
{
	constexpr int jump_baseDepth = 10;

	if (ON_COLLISION == COLLISION.PixelCollisionCheck(transform->position + VEC(0, jump_baseDepth)))
	{
		bJumpEnable = true;
	}
	else
	{
		bJumpEnable = false;
	}
}

void Player::StateProcess(float dt)
{
	if (playerState != playerPrevState || 
		playerLevel != playerPrevLevel)
	{
		SetTextureWithState();
	}

	playerPrevState = playerState;
	playerPrevLevel = playerLevel;
}

void Player::EffectProcess(float dt)
{
	if (playerState == IDLE)
		return;

	frameSkip_smoke += dt;

	if (frameSkip_smoke >= delay_smoke)
	{
		const Vector3 offset_smoke(-100, 0, 0);

		InstanceEx(ScaleEffect)(7)->Setup(GETTEX("SMOKE"),
			transform->position + offset_smoke,
			VEC(0.2, 0.2), 10, transform->rot, 0.2f);

		frameSkip_smoke = 0;
	}
}

void Player::CheetProcess(float dt)
{
#if CHEET_MODE
	if (GetKeyDown('1')) itemInfo[DOUBLE_JUMP].ItemOn(10.0f);
	if (GetKeyDown('2')) itemInfo[SPEED_UP].ItemOn(-1.0f);
	if (GetKeyDown('3')) itemInfo[RANGE_UP].ItemOn(10.0f);
	if (GetKeyDown('4')) itemInfo[TRACKING_BULLET].ItemOn(10.0f);
	if (GetKeyDown('5')) itemInfo[THREE_DIR_BULLET].ItemOn(10.0f);
	if (GetKeyDown('6')) itemInfo[NUCLEAR].Reset(0.0f, 2);

	if (GetKeyDown(VK_F1)) bPlayerInvinc = !bPlayerInvinc;
	if (GetKeyDown(VK_F2)) Degrade();
	if (GetKeyDown(VK_F3)) Upgrade();
#endif
}

void Player::CreateCannons()
{
	pCannon					  = InstanceEx(Cannon)(3);
	pTopCannon				  = InstanceEx(TopCannon)(3);
	pCannon->vOffset		  = VEC(120, -45);
	pTopCannon->vOffset		  = VEC(0, 0);
	pTopCannon->fCannonLength = 200.0f;

	pCannon->SetPlayer(this);
	pTopCannon->SetPlayer(this);
}

void Player::CreateUI()
{
	auto scaleEft = InstanceEx(ScaleEffect)(20);

	scaleEft->Setup(GETTEX("READY"), VEC(HALF_X, 200), VEC(0.2, 0.2), 5, 0, 1.5f);
	scaleEft->renderer->renderType = SCREEN;

	scaleEft->SetEndFunc([&]() {

		auto scaleEft = InstanceEx(ScaleEffect)(20);

		scaleEft->Setup(GETTEX("GO"), VEC(HALF_X, 200), VEC(0.2, 0.2), 5, 0, 1.5f);
		scaleEft->renderer->renderType = SCREEN;

		});
}

void Player::ReleaseCannons()
{
	pCannon->Kill();
	pTopCannon->Kill();
}

void Player::OnPlayerDeath()
{
	// 무적 처리
	if (bPlayerInvinc == true)
		return;

	Explode* explode = InstanceEx(Explode)(10); 
	explode->Setup(transform->position,
		GETTEX("EXPLODE_R"), 0.18);
	explode->transform->scale = Vector3(1.7, 1.7, 0);

	CAMERA.Shake(5500, 0.5f);

	ReleaseCannons();
	Kill();
}

void Player::SetTextureWithState()
{
	int frameS = 0, frameE = 0;
	float delay = 0.1f;

	switch (playerState)
	{
	case IDLE:
		frameS = 0; frameE = 5;
		break;
	case MOVE:
		frameS = 6; frameE = 11;
		break;
	}

	switch (playerLevel)
	{
	case PLAYER_TANK_LV1:
		renderer->SetTexture("PLAYER_L1");
		break;
	case PLAYER_TANK_LV2:
		renderer->SetTexture("PLAYER_L2");
		break;
	case PLAYER_TANK_LV3:
		renderer->SetTexture("PLAYER_L3");
		break;
	}

	renderer->SetFrame(frameS, frameE, delay);
}
