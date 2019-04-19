#pragma once
#include "Component.h"

class Renderer :
	public Component
{
public:
	int curFrame = 0, maxFrame = 0, startFrame = 0;
	float frameSkip = 0, frameDelay = 0;

	RENDER_MODE renderType = SCROLL;

	Vector3 vCenter = v3Zero;
	Texture* pTex = nullptr;

	int a = 255;
	int r = 255;
	int g = 255;
	int b = 255;

public:
	Renderer();
	virtual ~Renderer();

	void SetFrame(int s, int e, float d);
	void SetTexture(const string& key, int count = -1);
	void SetTexture(Texture* tex);
	void SetCenter();
	void SetCenter(Vector3 c);

	inline float Width(int index = 0) { return pTex->GetImage(index)->info.Width; }
	inline float Height(int index = 0) { return pTex->GetImage(index)->info.Height; }

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

