#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

