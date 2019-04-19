#include "DXUT.h"
#include "HappyEnding.h"

#include "Animator.h"
#include "Fade.h"
#include "Cursor.h"
#include "ScoreInput.h"

HappyEndingScene::HappyEndingScene()
{
}


HappyEndingScene::~HappyEndingScene()
{
}

void HappyEndingScene::Init()
{
	InstanceEx(Animator)(0)->Setup(v3Center,
		GETTEX("HAPPY_ENDING"),
		0.5, [&]() {
			InstanceEx(Fade)(20)->Setup(0,
				[]() {
					InstanceEx(ScoreInput)(21)->Setup(GETTEX("COMPLATE_UI"), "./RS/DATA/data.txt");
				},
				300, false);
		});

	InstanceEx(Cursor)(30);
	RESOURCE.SoundPlay("BACKGROUND2", true);
}

void HappyEndingScene::Update(float dt)
{
}

void HappyEndingScene::Render()
{
}

void HappyEndingScene::Destroy()
{
	RESOURCE.SoundStop("BACKGROUND2");

}
