#include "DXUT.h"
#include "BadEnding.h"

#include "Animator.h"
#include "Fade.h"
#include "Cursor.h"

#include "ScoreInput.h"

BadEndingScene::BadEndingScene()
{
}


BadEndingScene::~BadEndingScene()
{
}

void BadEndingScene::Init()
{
	InstanceEx(Animator)(0)->Setup(v3Center,
		GETTEX("SAD_ENDING"),
		0.5, [&]() {
			InstanceEx(Fade)(20)->Setup(0,
				[]() {
					InstanceEx(ScoreInput)(21)->Setup(GETTEX("FAIL_UI"), "./RS/DATA/data.txt");
				},
				300, false);
		});

	InstanceEx(Cursor)(30);
	RESOURCE.SoundPlay("BACKGROUND2", true);
}

void BadEndingScene::Update(float dt)
{
}

void BadEndingScene::Render()
{
}

void BadEndingScene::Destroy()
{
	RESOURCE.SoundStop("BACKGROUND2");

}
