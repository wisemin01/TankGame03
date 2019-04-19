#pragma once
#include "GameObject.h"

class Fade :
	public GameObject
{
public:
	float speed = 0;
	float endAlpha = 0;

	int fadeDir = 0;

	function<void()> endFade;

	bool fadingEnd = false;
	bool bAutoDel = false;

public:
	Fade();
	virtual ~Fade();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(int startAlpha, function<void()> func, float speed, bool auto_delete = true);
};

