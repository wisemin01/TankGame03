#include "DXUT.h"
#include "Stage2Scene.h"

#include "Player.h"
#include "ScrollMap.h"
#include "Ground.h"
#include "Water.h"
#include "Volcano.h"
#include "Mine.h"
#include "SavePoint.h"
#include "Portal.h"

#include "EnemyController.h"
#include "PlayerController.h"
#include "Cursor.h"

Stage2Scene::Stage2Scene()
{
}


Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Init()
{
	PlayerController::stage2Score = 0;

	CAMERA.Initialize(v3Zero);
	CAMERA.UseRange(0, 0, 99999, 850);

	InstanceEx(Cursor)(30);

	COLLISION.CreatePixelMap(GETTEX("S2_PIXELMAP"), 10);

	InstanceEx(ScrollMap)(-10)->Setup(GETTEX("S2_BACKGROUND", 0), Vector3(0, HALF_Y, 0), 200);
	InstanceEx(ScrollMap)(-9)->Setup(GETTEX("S2_BACKGROUND", 1), Vector3(0, HALF_Y, 0), 300);
	InstanceEx(Volcano)(-8)->Setup(v3Center);
	InstanceEx(ScrollMap)(-7)->Setup(GETTEX("S2_BACKGROUND", 2), Vector3(0, HALF_Y, 0), 400);
	InstanceEx(ScrollMap)(-6)->Setup(GETTEX("S2_BACKGROUND", 3), Vector3(0, HALF_Y, 0), 500);
	InstanceEx(Water)(8)->Setup(Vector3(0, 730, 0), 5000);
	InstanceEx(Portal)(8)->Setup(Vector3(45700, 480, 0), "HAPPY_END");

	Ground::PlaceMapWithPixelCollision(GETTEX("S2_MAP"), v3Zero, &COLLISION.pixelMap, 1);
	Mine::CreateMineOnGround(1200, 100, 700, 900);
	SavePoint::CreateSavePoints(2000, 5);

	InstanceEx(EnemyController)(0, false)->Setup(5);
	InstanceEx(PlayerController)(20, true);

	RESOURCE.SoundPlay("BACKGROUND4", true);
}

void Stage2Scene::Update(float dt)
{
}

void Stage2Scene::Render()
{
}

void Stage2Scene::Destroy()
{
	RESOURCE.SoundStop("BACKGROUND4");
}
