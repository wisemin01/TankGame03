#pragma once
#include "GameObject.h"


class Button :
	public GameObject
{
public:
	function<void()> onClick;

	RECT range;
public:
	Button();
	virtual ~Button();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Texture* tex, Vector3 pos, function<void()> func);
};

