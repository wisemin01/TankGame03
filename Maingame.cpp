#include "DXUT.h"
#include "Maingame.h"

#include "LoadScene.h"
#include "IntroScene.h"
#include "TitleScene.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"

#include "HappyEnding.h"
#include "BadEnding.h"

Maingame::Maingame()
{
}


Maingame::~Maingame()
{
}

void Maingame::Init()
{
	SCENE.AddScene("LOAD"	, new LoadScene);
	SCENE.AddScene("INTRO"	, new IntroScene );
	SCENE.AddScene("TITLE"	, new TitleScene );
	SCENE.AddScene("STAGE1"	, new Stage1Scene);
	SCENE.AddScene("STAGE2"	, new Stage2Scene);
	SCENE.AddScene("HAPPY_END", new HappyEndingScene);
	SCENE.AddScene("BAD_END", new BadEndingScene);

	SCENE.ChangeScene("LOAD");
}

void Maingame::Update(float dt)
{
	INPUT.KeyInput(dt);
	SCENE.Update(dt);
	CAMERA.Update(dt);

#if CHEET_MODE
	if (GetKeyDown(VK_F4)) SCENE.ChangeScene("TITLE");
	if (GetKeyDown(VK_F5)) SCENE.ChangeScene("STAGE1");
	if (GetKeyDown(VK_F6)) SCENE.ChangeScene("STAGE2");
	if (GetKeyDown(VK_F7)) SCENE.ChangeScene("HAPPY_END");
	if (GetKeyDown(VK_F8)) SCENE.ChangeScene("BAD_END");
#endif
}

void Maingame::Render()
{
	RESOURCE.Begin();
	SCENE.Render();
	RESOURCE.End();
}

void Maingame::Destroy()
{
	ObjectManager	::ReleaseInstance();
	CollisionManager::ReleaseInstance();
	SceneManager	::ReleaseInstance();
	InputManager	::ReleaseInstance();
	CameraManager	::ReleaseInstance();
	ResourceManager	::ReleaseInstance();
	FileManager		::ReleaseInstance();
}

void Maingame::OnReset()
{
	RESOURCE.OnReset();
}

void Maingame::OnLost()
{
	RESOURCE.OnLost();
}