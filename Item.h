#pragma once
#include "GameObject.h"

class Item :
	public GameObject
{
public:
	ITEM_TYPE itemType = ITEM_END;

	float delay = 0;
public:
	Item();
	virtual ~Item();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void Setup(Vector3 pos);
};

