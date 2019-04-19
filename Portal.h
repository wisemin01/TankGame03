#pragma once
#include "GameObject.h"

class Player;
class Portal :
	public GameObject
{
public:
	Player * player = nullptr;
	string nextScene;
	float rotIndex = 5.0f;
public:
	Portal();
	virtual ~Portal();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 position, const string& next_scene_key);
};

