#include "DXUT.h"
#include "ScaleEffect.h"


ScaleEffect::ScaleEffect()
{
}


ScaleEffect::~ScaleEffect()
{
}

void ScaleEffect::Init()
{
	AC(Transform);
	AC(Renderer);
}

void ScaleEffect::Update(float dt)
{
	Lerp<Vector3>(transform->scale, v3Normal, scalingSpeed * dt);

	if (bStartDelay) {
		frameSkip += dt;

		if (delay < frameSkip)
		{
			if (useEndFunc)
				endFunc();

			Kill();
		}
	}
	else if (transform->scale > Vector3(0.98, 0.98, 0.98))
	{
		if (delay >= 0) {
			bStartDelay = true;
		}
	}
}

void ScaleEffect::Render()
{
}

void ScaleEffect::Destroy()
{
}

void ScaleEffect::Setup(Texture * tex, Vector3 pos, Vector3 startScale, float speed, float rot, float delay)
{
	renderer->SetTexture(tex);

	transform->position		= pos;
	transform->scale		= startScale;
	transform->rot			= rot;

	this->scalingSpeed		= speed;

	this->delay		= delay;
	frameSkip		= 0;
	bStartDelay		= false;
}

void ScaleEffect::SetEndFunc(function<void()> func)
{
	useEndFunc = true;
	endFunc = func;
}
