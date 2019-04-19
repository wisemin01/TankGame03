#include "DXUT.h"
#include "Button.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::Init()
{
	AC(Transform);
	AC(Renderer);

	renderer->renderType = SCREEN;
}

void Button::Update(float dt)
{
	Vector3 &p = transform->position;
	Vector3 m = INPUT.GetMouse();

	bool onMouse = false;

	if (m.x > range.left + p.x  &&
		m.x< range.right + p.x  &&
		m.y> range.top + p.y &&
		m.y < range.bottom + p.y)
	{
		onMouse = true;
		renderer->SetFrame(1, 1, 0);
		Lerp(transform->scale, VEC(1.2, 1.2), dt * 10);

		if (GetKeyUp(VK_LBUTTON))
		{
			onClick();
		}
	}
	else
	{
		onMouse = false;
		renderer->SetFrame(0, 0, 0);
		Lerp(transform->scale, VEC(1.0, 1.0), dt * 10);
	}
}

void Button::Render()
{
}

void Button::Destroy()
{
}

void Button::Setup(Texture * tex, Vector3 pos, function<void()> func)
{
	renderer->SetTexture(tex);
	transform->position = pos;

	onClick = func;

	float w = renderer->Width();
	float h = renderer->Height();

	SetRect(&range, -w / 2.f, -h / 2.f, w / 2.f, h / 2.f);
}
