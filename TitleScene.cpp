#include "DXUT.h"
#include "TitleScene.h"

#include "Button.h"
#include "Fade.h"
#include "Fluffy.h"
#include "Ground.h"
#include "Explode.h"
#include "Screen.h"
#include "Cursor.h"
#include "ScoreScreen.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	CAMERA.Initialize();
	
	InstanceEx(Cursor)(30);

	InstanceEx(Ground)(-5)->Setup(SCREEN, v3Zero, GETTEX("TITLE_B", 0));
	InstanceEx(Ground)(-4)->Setup(SCREEN, v3Zero, GETTEX("TITLE_B", 1));
	InstanceEx(Ground)(-3)->Setup(SCREEN, v3Zero, GETTEX("TITLE_B", 2));

	InstanceEx(Explode)(-2)->Setup(v3Zero, GETTEX("TITLE_EX"), 0.2, true);

	InstanceEx(Ground)(-1)->Setup(SCREEN, v3Zero, GETTEX("TITLE_B", 3));

	InstanceEx(Fluffy)(0)->Setup(GETTEX("TITLE_EN", 0), VEC(0, 10), 50);
	InstanceEx(Fluffy)(1)->Setup(GETTEX("TITLE_EN", 1), VEC(0, -10), 40);
	InstanceEx(Fluffy)(2)->Setup(GETTEX("TITLE_EN", 2), VEC(0, 20), 45);
	InstanceEx(Fluffy)(3)->Setup(GETTEX("TITLE_EN", 3), VEC(0, -20), 35);
	InstanceEx(Fluffy)(4)->Setup(GETTEX("TITLE_EN", 4), VEC(0, 15), 55);

	InstanceEx(Button)(5)->Setup(GETTEX("START_BTN"),
		VEC(640, 437), [&]() { InstanceEx(Fade)(50)->Setup(0, []() {
			SCENE.ChangeScene("STAGE1"); }, 300, false); });
	InstanceEx(Button)(5)->Setup(GETTEX("RANK_BTN"),
		VEC(640, 613), [&]() { InstanceEx(ScoreScreen)(10)->Setup(v3Zero, GETTEX("RANK")); });
	InstanceEx(Button)(5)->Setup(GETTEX("CREDIT_BTN"),
		VEC(1160, 340), [&]() { InstanceEx(Screen)(10)->Setup(v3Zero, GETTEX("CREDIT")); });
	InstanceEx(Button)(5)->Setup(GETTEX("INFO_BTN"),
		VEC(1160, 486), [&]() { InstanceEx(Screen)(10)->Setup(v3Zero, GETTEX("INFO")); });
	InstanceEx(Button)(5)->Setup(GETTEX("HOWTO_BTN"),
		VEC(1160, 638), [&]() { InstanceEx(Screen)(10)->Setup(v3Zero, GETTEX("HOWTO")); });
	InstanceEx(Button)(5)->Setup(GETTEX("EXIT_BTN"),
		VEC(1216, 71), [&]() { PostQuitMessage(0); });

	InstanceEx(Ground)(6)->SetupCenter(SCREEN, VEC(640, 200), GETTEX("TITLE"));

	RESOURCE.SoundPlay("BACKGROUND2", true);
}

void TitleScene::Update(float dt)
{
}

void TitleScene::Render()
{
}

void TitleScene::Destroy()
{
	RESOURCE.SoundStop("BACKGROUND2");
}
