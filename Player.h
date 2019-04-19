#pragma once
#include "GameObject.h"
#include "ItemInfo.h"

// PLAYER ANIMATION FRAME : IDLE 1 ~ 6, MOVE 7 ~ 12

class Cannon;
class TopCannon;
class Player :
	public GameObject
{
private:
	// PREV
	STATE		  playerPrevState	= IDLE;
	PLAYER_LEVEL  playerPrevLevel	= PLAYER_TANK_LV1;
public:
	// CUR
	STATE		  playerState		= IDLE;
	PLAYER_LEVEL  playerLevel		= PLAYER_TANK_LV1;
	float		  playerSpeed		= 36;

	bool		  bJumpEnable		= false;
	bool		  bDoubleJumpEnable = false;

	bool		  bPlayerInvinc		= false;
	bool		  bPlayerControll	= true;
public:
	float		  frameSkip_smoke	= 0;
	float		  delay_smoke		= 0;
public:
	Cannon		* pCannon			= nullptr;
	TopCannon	* pTopCannon		= nullptr;

public:
	ItemInfo	  itemInfo[ITEM_TYPE::ITEM_END];
public:
	Player() { tag = "PLAYER"; }
	virtual ~Player() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Upgrade(int up_level = 1);
	void Degrade(int down_level = 1);

	void Setup(Vector3 startPos);
	void UseItem(ITEM_TYPE type, float delay, int plus_count = 1);

private:
	void SetTextureWithState();

	void InputProcess			(float dt);
	void PixelCollisionProcess	(float dt);
	void AttackProcess			(float dt);
	void ItemProcess			(float dt);
	void LifeProcess			(float dt);
	void JumpProcess			(float dt);
	void StateProcess			(float dt);
	void EffectProcess			(float dt);

	void CheetProcess(float dt);

private:
	void CreateCannons();
	void CreateUI();
	void ReleaseCannons();

	void OnPlayerDeath();
};

