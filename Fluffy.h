#pragma once
#include "GameObject.h"
class Fluffy :
	public GameObject
{
public:
	float minusY	= 0;
	float plusY		= 0;

	bool bDown		= false;
public:
	Fluffy();
	virtual ~Fluffy();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Texture* tex, Vector3 pos, float heightDepth);
};

