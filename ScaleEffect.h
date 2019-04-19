#pragma once
#include "GameObject.h"
class ScaleEffect :
	public GameObject
{
public:
	float	scalingSpeed	= 0.0f;

	float	delay		= 0;
	float	frameSkip	= 0;
	bool	bStartDelay = 0;

	bool	useEndFunc	= false;
	function<void()> endFunc;
public:
	ScaleEffect();
	virtual ~ScaleEffect();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Texture* tex, Vector3 pos, Vector3 startScale, float speed, float rot = 0, float delay = -1);
	void SetEndFunc(function<void()> func);
};

