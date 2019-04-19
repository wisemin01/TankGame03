#include "DXUT.h"
#include "Animator.h"


Animator::Animator()
{
}


Animator::~Animator()
{
}

void Animator::Init()
{
	AC(Transform);
	AC(Renderer);

	renderer->renderType = SCREEN;

	bEndAnimate = false;
}

void Animator::Update(float dt)
{
	if (bEndAnimate)
	{

	}
	else
	{

		if (renderer->curFrame == renderer->maxFrame)
		{
			renderer->SetFrame(renderer->maxFrame, renderer->maxFrame, 0);
			endFunc();
			bEndAnimate = true;
		}

		if (GetKeyDown(VK_LBUTTON)) {
			endFunc();
			bEndAnimate = true;
		}
	}
}

void Animator::Render()
{
}

void Animator::Destroy()
{
}

void Animator::Setup(Vector3 pos, Texture * tex, float delay, function<void()> end)
{
	transform->position = pos;
	renderer->SetTexture(tex);

	renderer->SetFrame(0, tex->size() - 1, delay);

	endFunc = end;
}
