#include "DXUT.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	Clear();
}

Scene * SceneManager::AddScene(const string & key, Scene* pScene)
{
	if (!pScene)
		return nullptr;

	auto f = mapScenes.find(key);

	if (f == mapScenes.end())
	{
		pScene->sKey = key;

		mapScenes.insert(make_pair(key, pScene));
		return pScene;
	}

	return f->second;
}

void SceneManager::ChangeScene(const string & key)
{
	auto f = mapScenes.find(key);

	if (f != mapScenes.end())
	{
		pNext = f->second;
		return;
	}

	return;
}

void SceneManager::Update(float dt)
{
	if (pNext)
	{
		if (pNow)
		{
			OBJECT.Reset();
			COLLISION.Reset();
			pNow->Destroy();
		}

		pNow = pNext;
		pNow->Init();
		pNext = nullptr;
	}

	if (pNow) {
		pNow->Update(dt);
		OBJECT.Update(dt);
		COLLISION.FrameCheck(dt);
	}
}

void SceneManager::Render()
{
	if (pNow)
	{
		pNow->Render();
		OBJECT.Render();
	}
}

void SceneManager::Clear()
{
	if (pNow) pNow->Destroy();

	for (auto iter : mapScenes) SAFE_DELETE(iter.second);

	mapScenes.clear();
}
