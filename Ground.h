#pragma once
#include "GameObject.h"
class Ground :
	public GameObject
{
public:
	float lifeTime = 0;
	float frameSkip = 0;

	bool useLifeTime = false;
public:
	Ground();
	virtual ~Ground();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(RENDER_MODE mode, Vector3 pos, Texture* tex);
	void SetupCenter(RENDER_MODE mode, Vector3 pos, Texture* tex);

	void UseLifeTime(float lifeTime);

public:
	static void PlaceMapWithPixelCollision(Texture* tex, Vector3 offset, PixelMap* map, int layer = 0);
};

