#pragma once
#include "Scene.h"
class Stage2Scene :
	public Scene
{
public:
	Stage2Scene();
	virtual ~Stage2Scene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

