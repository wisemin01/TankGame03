#pragma once
#include "GameObject.h"
class ScrollMap :
	public GameObject
{
public:
	int scroll;
	float scrollSpeed;

	float backX;
	float frontX;

	float cameraHeight;

	Texture* tex;
public:
	ScrollMap();
	virtual ~ScrollMap();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(const string& key, Vector3 pos, float speed);
	void Setup(Texture* text, Vector3 pos, float speed);
};

