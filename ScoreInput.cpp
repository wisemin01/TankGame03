#include "DXUT.h"
#include "ScoreInput.h"

#include "Ground.h"
#include "Button.h"

#include "PlayerController.h"
#include "Fade.h"

ScoreInput::ScoreInput()
{
}


ScoreInput::~ScoreInput()
{
}

void ScoreInput::Init()
{
	AC(Transform);
	AC(Renderer);

	InstanceEx(Button)(22)->Setup(GETTEX("END_EXIT_BTN"),
		VEC(515, 515), [&]() {
			InstanceEx(Fade)(50)->Setup(0, [&]() {
				SaveToFile(); SCENE.ChangeScene("TITLE");
				}, 300, false);
		});
	InstanceEx(Button)(22)->Setup(GETTEX("END_RE_BTN"),
		VEC(755, 515), [&]() { 
			InstanceEx(Fade)(50)->Setup(0, [&]() {
				SaveToFile(); SCENE.ChangeScene("STAGE1");
				}, 300, false);
		});

	renderer->renderType = SCREEN;

	scoreString = to_string(PlayerController::stage1Score + PlayerController::stage2Score);
	tempString = "AAA";
}

void ScoreInput::Update(float dt)
{
	// 65 ~ 90, 97 ~ 122

	for (int i = 65; i < 90; i++)
	{
		if (GetKeyDown(i) || GetKeyDown(32 + i))
		{
			if (tempString.size() < 3)
				tempString += (char)i;
		}
	}

	if (GetKeyDown(VK_BACK))
	{
		if (tempString.size() > 0)
			tempString.erase(tempString.size() - 1, 1);
	}
}

void ScoreInput::Render()
{
	RESOURCE.DrawString(tempString, VEC(555, 251), 50, 0xFFFFFFFF);
	RESOURCE.DrawString(scoreString, VEC(555, 331), 50, 0xFFFFFFFF);
}

void ScoreInput::Destroy()
{
}

void ScoreInput::Setup(Texture * tex, const string& file)
{
	renderer->SetTexture(tex);
	transform->position = v3Center + VEC(0, -50);
	filePath = file;
}

void ScoreInput::SaveToFile()
{
	FILEMGR.Clear();

	FILEMGR.GetFileData(filePath);

	if (tempString.size() == 0)
		tempString = "NULL";

	FILEMGR.InsertData(tempString, PlayerController::stage1Score + PlayerController::stage2Score);

	FILEMGR.SetFileData(filePath);
}
