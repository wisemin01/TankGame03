#pragma once
#include "Singleton.h"

class Scene;
class SceneManager :
	public Singleton<SceneManager>
{
public:
	map<string, Scene*> mapScenes;

	Scene* pNow = nullptr;
	Scene* pNext = nullptr;
public:
	SceneManager();
	virtual ~SceneManager();

	Scene* AddScene(const string& key, Scene* pScene);
	void ChangeScene(const string& key);

	void Update(float dt);
	void Render();

	void Clear();
};

#define SCENE SceneManager::GetInstance()