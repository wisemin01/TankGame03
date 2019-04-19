#include "DXUT.h"
#include "Collider.h"

#include "GameObject.h"
#include "Transform.h"

Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::Create(float l, float t, float r, float b, function<void(Collider*)> func)
{
	resize(l, t, r, b);
	onCollisionFunc = func;
	COLLISION.Register(this);
}

void Collider::Create(float w, float h, function<void(Collider*)> func)
{
	resize(w, h);
	onCollisionFunc = func;
	COLLISION.Register(this);
}

void Collider::CreateWithTexture(Texture* tex, function<void(Collider*)> func)
{
	resize(tex);
	onCollisionFunc = func;
	COLLISION.Register(this);
}

void Collider::Init()
{
	gameObject->collider = this;
}

void Collider::Destroy()
{
	if (gameObject->collider == this)
		gameObject->collider = nullptr;

	COLLISION.UnRegister(this);
}

RECT Collider::GetWorldRange()
{
	RECT r;
	Vector3 s = gameObject->transform->scale;
	Vector3 p = gameObject->transform->position;

	SetRect(&r, range.left * s.x + p.x,
				range.top * s.y + p.y,
				range.right * s.x + p.x,
				range.bottom * s.y + p.y);

	return r;
}

size_t Collider::Width()
{
	return abs(range.right - range.left) * gameObject->transform->scale.x;
}

size_t Collider::Height()
{
	return abs(range.bottom - range.top) * gameObject->transform->scale.y;
}

void Collider::resize(float w, float h)
{
	SetRect(&range, -w / 2.f, -h / 2.f, w / 2.f, h / 2.f);
}

void Collider::resize(float l, float t, float r, float b)
{
	SetRect(&range, l, t, r, b);
}

void Collider::resize(Texture * tex)
{
	float w = tex->GetImage(0)->info.Width;
	float h = tex->GetImage(0)->info.Height;

	SetRect(&range, -w / 2.f, -h / 2.f, w / 2.f, h / 2.f);
}

bool Collider::CompareTag(const string & tag)
{
	return (bool)(tag == gameObject->tag);
}

void Collider::OnCollision(Collider * other)
{
	onCollisionFunc(other);
}
