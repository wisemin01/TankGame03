#pragma once
#include "Scene.h"
class Stage1Scene :
	public Scene
{
public:
	Stage1Scene();
	virtual ~Stage1Scene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

