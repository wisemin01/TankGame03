#include "DXUT.h"
#include "Renderer.h"
#include "GameObject.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::SetFrame(int s, int e, float d)
{
	startFrame	= s;
	curFrame	= s;
	maxFrame	= e;
	frameSkip	= 0;
	frameDelay	= d;
}

void Renderer::SetTexture(const string & key, int count)
{
	pTex = GETTEX(key, count);
	SetCenter();
}

void Renderer::SetTexture(Texture * tex)
{
	pTex = tex;
	SetCenter();
}

void Renderer::SetCenter()
{
	vCenter = Vector3(pTex->GetImage(0)->info.Width / 2.f, pTex->GetImage(0)->info.Height / 2.f, 0);
}

void Renderer::SetCenter(Vector3 c)
{
	vCenter = c;
}

void Renderer::Init()
{
	gameObject->renderer = this;
}

void Renderer::Update(float dt)
{
	frameSkip += dt;

	if (frameSkip >= frameDelay)
	{
		if (++curFrame > maxFrame)
		{
			curFrame = startFrame;
		}
		frameSkip = 0;
	}
}

void Renderer::Render()
{
	RESOURCE.SetRenderType(renderType);

	GO->transform->ApplyTransform();

	RESOURCE.Draw(pTex->GetImage(curFrame), vCenter, D3DCOLOR_ARGB(a, r, g, b));
}

void Renderer::Destroy()
{
	if (gameObject->renderer == this)
		gameObject->renderer = nullptr;
}
