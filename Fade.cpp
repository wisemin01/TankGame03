#include "DXUT.h"
#include "Fade.h"


Fade::Fade()
{
}


Fade::~Fade()
{
}

void Fade::Init()
{
	AC(Transform);
	AC(Renderer);

	renderer->renderType = SCREEN;
	renderer->SetTexture("BLACK");
}

void Fade::Update(float dt)
{
	if (fadingEnd)
	{
		if (bAutoDel)
		{
			Kill();
		}
		else
		{
			// NONE 
		}
	}
	else {
		renderer->a += fadeDir * speed * dt;

		if (fadeDir < 0)
		{
			if (renderer->a < endAlpha)
			{
				renderer->a = endAlpha;
				endFade();
				fadingEnd = true;
			}
		}
		else if (fadeDir > 0)
		{
			if (renderer->a > endAlpha)
			{
				renderer->a = endAlpha;
				endFade();
				fadingEnd = true;
			}
		}
	}
}

void Fade::Render()
{
}

void Fade::Destroy()
{
}

void Fade::Setup(int startAlpha, function<void()> func, float speed, bool auto_delete)
{
	transform->position = v3Center;
	renderer->a = startAlpha;
	endFade = func;
	this->speed = speed;

	endAlpha = startAlpha == 0 ? 255 : 0;
	fadeDir = startAlpha == 0 ? 1 : -1;

	bAutoDel = auto_delete;
}
