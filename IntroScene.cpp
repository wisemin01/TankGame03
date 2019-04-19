#include "DXUT.h"
#include "IntroScene.h"

#include "Animator.h"
#include "Fade.h"
#include "Cursor.h"

IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::Init()
{
	InstanceEx(Animator)(0)->Setup(v3Center,
		GETTEX("INTRO_ANIMATION"),
		0.5, [&]() { InstanceEx(Fade)(50)->Setup(0, []() {
			SCENE.ChangeScene("TITLE");
			}, 300); });

	InstanceEx(Cursor)(30);
	
	RESOURCE.SoundPlay("BACKGROUND2", true);
}

void IntroScene::Update(float dt)
{
}

void IntroScene::Render()
{
}

void IntroScene::Destroy()
{
	RESOURCE.SoundStop("BACKGROUND2");
}
