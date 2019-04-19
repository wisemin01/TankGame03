#include "DXUT.h"
#include "GameObject.h"

#include "Component.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::ComUpdate(float dt)
{
	for (auto iter : listCom)
	{
		if (iter->bActive)
			iter->Update(dt);
	}
}

void GameObject::ComRender()
{
	for (auto iter : listCom)
	{
		if (iter->bActive)
			iter->Render();
	}
}

void GameObject::ComDestroy()
{
	for (auto iter : listCom)
	{
		iter->Destroy();
		SAFE_DELETE(iter);
	}

	listCom.clear();
}
