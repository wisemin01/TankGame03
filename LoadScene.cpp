#include "DXUT.h"
#include "LoadScene.h"

#include "Cursor.h"
#include "Ground.h"

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	ADDTEX("CURSOR", "./RS/UI/MOUSE.png");
	ADDTEX("LOADING", "./RS/UI/LOAD.png");

	// 사운드
	RESOURCE.AddSound("BACKGROUND1", L"./RS/SOUND/(1).wav");
	RESOURCE.AddSound("BACKGROUND2", L"./RS/SOUND/(2).wav");
	RESOURCE.AddSound("BACKGROUND3", L"./RS/SOUND/(3).wav");
	RESOURCE.AddSound("BACKGROUND4", L"./RS/SOUND/(4).wav");

	RESOURCE.AddSound("EXPLODE1", L"./RS/SOUND/E(1).wav");
	RESOURCE.AddSound("EXPLODE2", L"./RS/SOUND/E(2).wav");
	RESOURCE.AddSound("EXPLODE3", L"./RS/SOUND/E(3).wav");

	InstanceEx(Cursor)(30);
	InstanceEx(Ground)(0)->SetupCenter(SCREEN, v3Center, GETTEX("LOADING"));

	bLoading = false;

	loadTh = thread([&]() { ThreadLoad(); });

	RESOURCE.SoundPlay("BACKGROUND3", true);
}

void LoadScene::Update(float dt)
{
	if (bLoading == true) {
		if (loadTh.joinable())
		{
			loadTh.join();
			SCENE.ChangeScene("INTRO");
		}
	}
}

void LoadScene::Render()
{
}

void LoadScene::Destroy()
{
	RESOURCE.SoundStop("BACKGROUND3");
}

void LoadScene::ThreadLoad()
{
	// 공용 텍스쳐

	ADDTEX("PLAYER_L1", "./RS/OBJECT/PLAYER/L1(%d).png", 12);
	ADDTEX("PLAYER_L2", "./RS/OBJECT/PLAYER/L2(%d).png", 12);
	ADDTEX("PLAYER_L3", "./RS/OBJECT/PLAYER/L3(%d).png", 12);
	ADDTEX("PLAYER_TOP", "./RS/OBJECT/PLAYER/TOP.png");

	ADDTEX("ENEMY", "./RS/OBJECT/ENEMY/ENEMY(%d).png", 4);
	ADDTEX("DROP_MINE", "./RS/OBJECT/ENEMY/DROP_MINE(%d).png", 4);
	ADDTEX("MINE", "./RS/OBJECT/ENEMY/MINE(%d).png", 4);

	ADDTEX("WATER", "./RS/OBJECT/WATER.png");
	ADDTEX("VOLCANO", "./RS/OBJECT/VOLCANO/V(%d).png", 5);
	ADDTEX("VOLCANO_WARNING", "./RS/EFFECT/WARNING.png");

	ADDTEX("METEOR", "./RS/OBJECT/METEOR/(%d).png", 2);
	ADDTEX("SAVE", "./RS/OBJECT/FLAG/(%d).png", 5);

	ADDTEX("BULLET_A", "./RS/EFFECT/BULLET/DEFAULT.png");
	ADDTEX("BULLET_B", "./RS/EFFECT/BULLET/ROT.png");
	ADDTEX("BULLET_C", "./RS/EFFECT/BULLET/DOWN.png");
	ADDTEX("NUCLEAR", "./RS/EFFECT/BULLET/NUCLEAR.png");
	ADDTEX("RING_EFT", "./RS/EFFECT/BULLET/EFT(%d).png", 2);
	ADDTEX("EXPLODE_B", "./RS/EFFECT/EXPLODE/B(%d).png", 6);
	ADDTEX("EXPLODE_R", "./RS/EFFECT/EXPLODE/R(%d).png", 6);
	ADDTEX("SMOKE", "./RS/EFFECT/SMOKE.png");
	ADDTEX("SCREEN_WHITE", "./RS/EFFECT/SCREEN.png");
	ADDTEX("SCREEN_SPEEDUP", "./RS/EFFECT/SPEEDUP.png");
	ADDTEX("PORTAL", "./RS/EFFECT/PORTAL/(%d).png", 3);

	ADDTEX("ITEM_INFO", "./RS/UI/ITEM_INFO/(%d).png", 6);
	ADDTEX("ITEM", "./RS/UI/ITEM/(%d).png", 6);
	ADDTEX("HEART", "./RS/UI/HEART.png");
	ADDTEX("TANK", "./RS/UI/TANK.png");
	ADDTEX("TIME", "./RS/UI/TIME.png");
	ADDTEX("PROGRESS", "./RS/UI/PROG(%d).png", 2);
	ADDTEX("BLACK", "./RS/UI/BLACK.png");

	ADDTEX("CREDIT_BTN", "./RS/UI/TITLE/C(%d).png", 2);
	ADDTEX("EXIT_BTN", "./RS/UI/TITLE/E(%d).png", 2);
	ADDTEX("HOWTO_BTN", "./RS/UI/TITLE/H(%d).png", 2);
	ADDTEX("INFO_BTN", "./RS/UI/TITLE/I(%d).png", 2);
	ADDTEX("START_BTN", "./RS/UI/TITLE/S(%d).png", 2);
	ADDTEX("RANK_BTN", "./RS/UI/TITLE/R(%d).png", 2);

	ADDTEX("END_EXIT_BTN", "./RS/UI/ENDING/EXIT(%d).png", 2);
	ADDTEX("END_RE_BTN", "./RS/UI/ENDING/RE(%d).png", 2);

	ADDTEX("COMPLATE_UI", "./RS/UI/ENDING/COMPLATE.png");
	ADDTEX("FAIL_UI", "./RS/UI/ENDING/FAIL.png");

	ADDTEX("CREDIT", "./RS/UI/TITLE/CREDIT.png");
	ADDTEX("HOWTO", "./RS/UI/TITLE/HOWTO.png");
	ADDTEX("INFO", "./RS/UI/TITLE/INFO.png");
	ADDTEX("RANK", "./RS/UI/TITLE/RANK.png");
	ADDTEX("TITLE", "./RS/UI/TITLE/TITLE.png");
	ADDTEX("READY", "./RS/UI/READY.png");
	ADDTEX("GO", "./RS/UI/GO.png");
	ADDTEX("CLEAR", "./RS/UI/CLEAR.png");

	// 스테이지 한정 텍스쳐

	ADDTEX("S1_PIXELMAP", "./RS/DATA/S1MINIMAP/(%d).png", 3);
	ADDTEX("S1_BACKGROUND", "./RS/OBJECT/STAGE1MAP/(%d).png", 5);
	ADDTEX("S1_MAP", "./RS/OBJECT/STAGE1MAP/M(%d).png", 3);

	ADDTEX("S2_PIXELMAP", "./RS/DATA/S2MINIMAP/(%d).png", 3);
	ADDTEX("S2_BACKGROUND", "./RS/OBJECT/STAGE2MAP/(%d).png", 4);
	ADDTEX("S2_MAP", "./RS/OBJECT/STAGE2MAP/M(%d).png", 3);

	ADDTEX("INTRO_ANIMATION", "./RS/OBJECT/INTRO/(%d).png", 31);
	ADDTEX("HAPPY_ENDING", "./RS/OBJECT/HAPPY_END/(%d).png", 41);
	ADDTEX("SAD_ENDING", "./RS/OBJECT/SAD_END/(%d).png", 27);

	ADDTEX("TITLE_B", "./RS/OBJECT/TITLE/B(%d).png", 4);
	ADDTEX("TITLE_EX", "./RS/OBJECT/TITLE/EX(%d).png", 6);
	ADDTEX("TITLE_EN", "./RS/OBJECT/TITLE/EN(%d).png", 5);

	ADDTEX("BLUR", "./RS/UI/BLUR.png");

	bLoading = true;
}
