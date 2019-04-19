#include "DXUT.h"
#include "ScoreScreen.h"


ScoreScreen::ScoreScreen()
{
}


ScoreScreen::~ScoreScreen()
{
}

void ScoreScreen::Init()
{
	Screen::Init();

	positionIndices[0] = VEC(590, 293);
	positionIndices[1] = VEC(440, 340);
	positionIndices[2] = VEC(740, 372);
}

void ScoreScreen::Update(float dt)
{
	Screen::Update(dt);

	if (transform->scale.x > 0.9f)
		bRender = true;
	else
		bRender = false;
}

void ScoreScreen::Render()
{
	if (bRender == false) return;

	for (int i = 0; i < scoreCount; i++) {
		RESOURCE.DrawString(scoreArray[i].second, positionIndices[i], 50, 0xFFFFFFFF);
		RESOURCE.DrawString(to_string(scoreArray[i].first), positionIndices[i] + VEC(0, 35), 50, 0xFFFFFFFF);
	}
}

void ScoreScreen::Destroy()
{
}

void ScoreScreen::Setup(Vector3 pos, Texture * tex, int exit_key)
{
	Screen::Setup(pos, tex, exit_key);

	FILEMGR.GetFileData("./RS/DATA/data.txt");

	int i = 0;

	for (auto iter : FILEMGR.GetList())
	{
		scoreArray[i] = iter;

		if (++i > 2)
			break;
	}

	scoreCount = i;

	FILEMGR.Clear();
}
