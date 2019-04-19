#include "DXUT.h"
#include "Ground.h"


Ground::Ground()
{
	tag = "GROUND";
}


Ground::~Ground()
{
}

void Ground::Init()
{
	AC(Transform);
	AC(Renderer);
}

void Ground::Update(float dt)
{
	if (useLifeTime)
	{
		frameSkip += dt;

		if (frameSkip >= lifeTime)
		{
			Kill();
		}
	}
}

void Ground::Render()
{
}

void Ground::Destroy()
{
}

void Ground::Setup(RENDER_MODE mode, Vector3 pos, Texture * tex)
{
	renderer->SetTexture(tex);
	renderer->vCenter = v3Zero;
	renderer->renderType = mode;

	transform->position = pos;
}

void Ground::SetupCenter(RENDER_MODE mode, Vector3 pos, Texture * tex)
{
	renderer->SetTexture(tex);
	renderer->renderType = mode;

	transform->position = pos;
}

void Ground::UseLifeTime(float lifeTime)
{
	useLifeTime = true;
	this->lifeTime = lifeTime;
	frameSkip = 0;
}

void Ground::PlaceMapWithPixelCollision(Texture* tex, Vector3 offset, PixelMap * map, int layer)
{
	for (int i = 0; i < map->mapCount; i++)
	{
		InstanceEx(Ground)(layer)->Setup(SCROLL, 
			offset + Vector3(i*map->width, 0, 0),
			tex->GetImage(map->vecRandMap[i]));
	}
}
