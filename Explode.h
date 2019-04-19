#pragma once
#include "GameObject.h"
class Explode :
	public GameObject
{
public:
	bool useLoop = false;
public:
	Explode();
	virtual ~Explode();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, Texture* tex, float delay, bool isLoop = false);
};

