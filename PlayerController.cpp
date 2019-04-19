#include "DXUT.h"
#include "PlayerController.h"
#include "Player.h"

#include "EnemyController.h"
#include "Ground.h"
#include "Scene.h"
#include "Fade.h"

int PlayerController::playerHeart = 3;
int PlayerController::stage1Score = 0;
int PlayerController::stage2Score = 0;
Vector3 PlayerController::playerRespawn = Vector3(100, 300, 0);
bool PlayerController::stageClear = false;


PlayerController::PlayerController()
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::Init()
{
	AC(Transform);
	InstanceEx(Ground)(20)->SetupCenter(SCREEN, VEC(1078, 63), GETTEX("TIME"));

	playerHeart = 3;
	playerRespawn = Vector3(100, 300, 0);
	stageClear = false;

	pItem			= GETTEX("ITEM");
	pHeart			= GETTEX("HEART");
	pProgress		= GETTEX("PROGRESS");
	pPlayerInvinc	= GETTEX("SCREEN_WHITE");
	pPlayerSpeedup	= GETTEX("SCREEN_SPEEDUP");

	Scene* pNow		= SCENE.pNow;

	if (pNow) {
		if (pNow->sKey == "STAGE1")
			nowStageScore = &stage1Score;
		else if (pNow->sKey == "STAGE2")
			nowStageScore = &stage2Score;
		else
			nowStageScore = nullptr;
	}
	
	player = InstanceEx(Player)(2);
	player->Setup(playerRespawn);

	anyTime = 180.0f;
	stageEnd = false;

	(*nowStageScore) = 0;
}

void PlayerController::Update(float dt)
{
	anyTime -= dt;

	if (player) {
		// PROGRESS CALC
		gameProgress = (player->transform->position.x / COLLISION.pixelMap.mapWidth);
		
		if (anyTime <= 0)
		{
			player->life->OnAttack(100);
		}

		if (player->bLive == false)
		{
			OBJECT.TagClear("METEOR");
			player = nullptr;

			if (playerHeart < 1)
			{
				if (stageEnd == false)
				{
					stageEnd = true;
					InstanceEx(Fade)(50)->Setup(0, []() {SCENE.ChangeScene("BAD_END"); }, 300, false);
				}
			}
			else {
				InstanceEx(Fade)(50)->Setup(0, [&]() { Spawn(); }, 300);
			}
		}
	}

	ProcessScore();

	drawString[0] = "SCORE : ";
	drawString[0].append(to_string(*nowStageScore));
	drawString[1] = to_string((int)anyTime);
}

void PlayerController::Render()
{
	DrawScreen();
	DrawHeart();
	DrawItem();
	DrawProgress();

	RESOURCE.DrawString(drawString[0], VEC(650, 25), 75, 0xFFFFFFFF);
	RESOURCE.DrawString(drawString[1], VEC(1150, 25), 75, 0xFFFFFFFF);
}

void PlayerController::Destroy()
{

}

void PlayerController::Spawn()
{
	if (playerHeart < 1) {
		return;
	}
	playerHeart--;

	player = InstanceEx(Player)(2);
	player->Setup(playerRespawn);

	anyTime = 180.0f;
}

void PlayerController::DrawScreen()
{
	if (player)
	{
		if (player->bPlayerInvinc)
		{
			RESOURCE.SetRenderType(SCREEN);
			RESOURCE.SetTransform(v3Center, v3Normal, 0);
			RESOURCE.Draw(pPlayerInvinc, v3Center, D3DCOLOR_ARGB(130, 255, 255, 255));
		}
		if (player->itemInfo[SPEED_UP].enable)
		{
			RESOURCE.SetRenderType(SCREEN);
			RESOURCE.SetTransform(v3Center, v3Normal, 0);
			RESOURCE.Draw(pPlayerSpeedup, v3Center, D3DCOLOR_ARGB(135, 255, 255, 255));
		}
	}
}

void PlayerController::DrawHeart()
{
	RESOURCE.SetRenderType(SCREEN);

	const Vector3 start(97, 90, 0);

	Vector3 center;
	center.x = pHeart->GetImage(0)->info.Width  / 2.f;
	center.y = pHeart->GetImage(0)->info.Height / 2.f;
	center.z = 0;

	for (int i = 0; i < playerHeart; i++)
	{
		RESOURCE.SetTransform(start + VEC(i * 134, 0), v3Normal, 0);
		RESOURCE.Draw(pHeart, center, 0xFFFFFFFF);
	}
}

void PlayerController::DrawItem()
{
	if (player == nullptr)
		return;

	RESOURCE.SetRenderType(SCREEN);

	const Vector3 start(87, 212, 0);
	constexpr float depth = 97;

	Vector3 center;
	center.x = pItem->GetImage(0)->info.Width / 2.f;
	center.y = pItem->GetImage(0)->info.Height / 2.f;
	center.z = 0;

	int itemCount = 0;

	for (int i = 0; i < ITEM_TYPE::ITEM_END; i++)
	{
		if (player->itemInfo[i].enable)
		{
			RESOURCE.SetTransform(start + VEC(0, itemCount * depth), v3Normal, 0);
			RESOURCE.Draw(pItem->GetImage(i), center, 0xFFFFFFFF);
			itemCount++;
		}
	}
}

void PlayerController::DrawProgress()
{
	RESOURCE.SetRenderType(SCREEN);

	Vector3 start = VEC(197, 624);

	RESOURCE.SetTransform(start, v3Normal, 0);
	RESOURCE.Draw(pProgress->GetImage(0), v3Zero, 0xFFFFFFFF);

	RECT range;
	SetRect(&range, 0, 0,
		(float)pProgress->GetImage(1)->info.Width * gameProgress,
		pProgress->GetImage(1)->info.Height);

	RESOURCE.SetTransform(start, v3Normal, 0);
	RESOURCE.RectDraw(pProgress->GetImage(1), range, v3Zero, 0xFFFFFFFF);
}

void PlayerController::ProcessScore()
{
	constexpr int enemyKillScorePoint = 10;
	constexpr int playerAnyHeartPoint = 60;
	constexpr int playerAnyTimePoint = 2;
	constexpr int stageClearPoint = 500;

	(*nowStageScore) =	EnemyController::enemyKillCount * enemyKillScorePoint;
	(*nowStageScore) += PlayerController::playerHeart * playerAnyHeartPoint;
	(*nowStageScore) += PlayerController::anyTime * playerAnyTimePoint;
	(*nowStageScore) += PlayerController::stageClear ? stageClearPoint : 0;
}