#pragma once
#include "Scene.h"
class BadEndingScene :
	public Scene
{
public:

public:
	BadEndingScene();
	virtual ~BadEndingScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

