#pragma once
#include "GameObject.h"


class Screen :
	public GameObject
{
public:
	int exitKey = VK_LBUTTON;
public:
	Screen();
	virtual ~Screen();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, Texture* tex, int exit_key = VK_LBUTTON);
};

