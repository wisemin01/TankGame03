#pragma once
#include "GameObject.h"

class Animator :
	public GameObject
{
public:
	function<void()> endFunc;

	bool bMouseExit = true;
	bool bEndAnimate = false;
public:
	Animator();
	virtual ~Animator();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, Texture* tex, float delay, function<void()> end);
};

