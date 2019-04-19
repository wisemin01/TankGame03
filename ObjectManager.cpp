#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	Reset();
}

void ObjectManager::Update(float dt)
{
	listRender.clear();

	for (auto iter = listObj.begin(); iter != listObj.end();)
	{
		GameObject * p = *iter;

		if (p->bDeleteCheck)
		{
			p->ComDestroy();
			p->Destroy();
			SAFE_DELETE(p);

			iter = listObj.erase(iter);
		}
		else
		{
			if (p->bLive)
			{
				p->ComUpdate(dt);
				p->Update(dt);

				if (p->bScreen)
				{
					listRender.push_back(p);
				}
			}
			else
			{
				p->bDeleteCheck = true;
			}

			iter++;
		}
	}

	// SORTING

	listRender.sort([&](const GameObject* left, const GameObject* right) {
		// 레이어 정렬
		if (left->iLayer < right->iLayer) return true;
		// Y 기준 정렬
		else if (left->iLayer == right->iLayer)	return left->transform->position.y < right->transform->position.y;
		else return false;
		});
}

void ObjectManager::Render()
{
	for (auto iter : listRender)
	{
		iter->ComRender();
		iter->Render();
	}
}

void ObjectManager::Reset()
{
	for (auto iter : listObj)
	{
		iter->ComDestroy();
		iter->Destroy();
		SAFE_DELETE(iter);
	}

	listObj.clear();
	listRender.clear();
}

void ObjectManager::TagClear(const string & target_tag)
{
	for (auto iter : listObj)
	{
		if (iter->tag == target_tag)
		{
			iter->Kill();
		}
	}
}
