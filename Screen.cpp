#include "DXUT.h"
#include "Screen.h"


Screen::Screen()
{
}


Screen::~Screen()
{
}

void Screen::Init()
{
	AC(Transform);
	AC(Renderer);
}

void Screen::Update(float dt)
{
	Lerp(transform->scale, v3Normal, dt * 10);

	if (GetKeyDown(exitKey))
	{
		Kill();
	}
}

void Screen::Render()
{
}

void Screen::Destroy()
{
}

void Screen::Setup(Vector3 pos, Texture * tex, int exit_key)
{
	transform->position = pos;
	transform->scale = VEC(0.2, 0.2);
	renderer->SetTexture(tex);

	exitKey = exit_key;
}
