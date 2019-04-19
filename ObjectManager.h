#pragma once
#include "Singleton.h"

class GameObject;
class ObjectManager :
	public Singleton<ObjectManager>
{
public:
	list<GameObject*> listObj;
	list<GameObject*> listRender;
public:
	ObjectManager();
	virtual ~ObjectManager();

	template <class T>
	T* AddObject(int layer = 0, bool show = 1, bool active = 1)
	{
		T* obj = new T;

		obj->iLayer = layer;
		obj->bScreen = show;
		obj->bActive = active;
		obj->bLive = true;
		
		obj->Init();

		listObj.push_back(obj);
		return obj;
	}

	void Update(float dt);
	void Render();

	void Reset();

	void TagClear(const string& target_tag);
};

#define OBJECT ObjectManager::GetInstance()

#define Instance(type)		OBJECT.AddObject<type>()
#define InstanceEx(type)	OBJECT.AddObject<type>