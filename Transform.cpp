#include "DXUT.h"
#include "Transform.h"

#include "GameObject.h"

Transform::Transform()
{
}


Transform::~Transform()
{
}

void Transform::Init()
{
	gameObject->transform = this;
}

void Transform::Destroy()
{
	if (gameObject->transform == this)
		gameObject->transform = nullptr;
}

void Transform::ApplyTransform()
{
	RESOURCE.SetTransform(position + offset, scale, rot);
}
