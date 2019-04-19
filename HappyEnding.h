#pragma once
#include "Scene.h"

class HappyEndingScene :
	public Scene
{
public:
	HappyEndingScene();
	virtual ~HappyEndingScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

