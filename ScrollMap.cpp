#include "DXUT.h"
#include "ScrollMap.h"

ScrollMap::ScrollMap()
{
	tag = "SCROLL MAP";
}


ScrollMap::~ScrollMap()
{
}

void ScrollMap::Init()
{
	AC(Transform);

	scroll = 0;
	scrollSpeed = 0;
	cameraHeight = 0;
}

void ScrollMap::Update(float dt)
{
	int w = tex->GetImage(0)->info.Width;
	scroll -= dt * scrollSpeed;

	backX = scroll % w + transform->position.x;
	frontX = backX + w;

	cameraHeight = CAM_POS.y;
}

void ScrollMap::Render()
{
	RESOURCE.SetRenderType(SCREEN);

	RESOURCE.SetTransform(VEC(backX, transform->position.y - cameraHeight), transform->scale, 0);
	RESOURCE.Draw(tex->GetImage(0), v3Zero, 0xFFFFFFFF);

	RESOURCE.SetTransform(VEC(frontX, transform->position.y - cameraHeight), transform->scale, 0);
	RESOURCE.Draw(tex->GetImage(0), v3Zero, 0xFFFFFFFF);
}

void ScrollMap::Destroy()
{
}

void ScrollMap::Setup(const string & key, Vector3 pos, float speed)
{
	tex = GETTEX(key);
	transform->position = pos;
	scrollSpeed = speed;
}

void ScrollMap::Setup(Texture * text, Vector3 pos, float speed)
{
	tex = text;
	transform->position = pos;
	scrollSpeed = speed;
}
