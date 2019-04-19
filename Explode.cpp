#include "DXUT.h"
#include "Explode.h"


Explode::Explode()
{
	tag = "EXPLODE";
}


Explode::~Explode()
{
}

void Explode::Init()
{
	AC(Transform);
	AC(Renderer);
}

void Explode::Update(float dt)
{
	if (renderer->curFrame == renderer->maxFrame)
	{
		if (useLoop == false)
		{
			Kill();
		}
	}
}

void Explode::Render()
{
}

void Explode::Destroy()
{
}

void Explode::Setup(Vector3 pos, Texture * tex, float delay, bool isLoop)
{
	transform->position = pos;
	renderer->SetTexture(tex);

	renderer->SetFrame(0, tex->size() - 1, delay);

	useLoop = isLoop;
}
