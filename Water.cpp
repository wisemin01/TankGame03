#include "DXUT.h"
#include "Water.h"


Water::Water()
{
	tag = "WATER";
}


Water::~Water()
{
}

void Water::Init()
{
	AC(Transform);
	AC(Collider);

	waterTex = GETTEX("WATER");
}

void Water::Update(float dt)
{
	sinIndex += dt * 10;

	if (sinIndex > 100)
		sinIndex -= 100;

	ProcessWater(dt);
}

void Water::Render()
{
	RESOURCE.SetRenderType(SCROLL);

	constexpr int depth = 10;

	float leftCamera = CAMERA.vEye.x - HALF_X - depth;
	float rightCamera = CAMERA.vEye.x + HALF_X + depth;

	int startIndex = (leftCamera / width);
	int endIndex = (rightCamera / width);

	if (startIndex < 0)
		startIndex = 0;
	if (endIndex < 0)
		endIndex = 0;
	if (startIndex > indiceCount - 1)
		startIndex = indiceCount - 1;
	if (endIndex > indiceCount - 1)
		endIndex = indiceCount - 1;

	for (int i = startIndex; i < endIndex; i++)
	{
		waterIndex& iter = waterIndices[i];

		RESOURCE.SetTransform(VEC(iter.x, iter.y
			+ sin(sinIndex + iter.x * 0.02) * 5), v3Normal, 0);

		RESOURCE.Draw(waterTex, v3Zero, 0xFFFFFFFF);
	}
}

void Water::Destroy()
{
}

void Water::Setup(Vector3 pivot, int indiceCnt)
{
	width = waterTex->GetImage(0)->info.Width - 3;
	height = waterTex->GetImage(0)->info.Height;

	entireWidth = width * indiceCnt;

	transform->position = pivot;

	indiceCount = indiceCnt;

	waterIndices.reserve(indiceCnt);

	for (int i = 0; i < indiceCnt; i++)
	{
		waterIndices.push_back(waterIndex(pivot.x + i * width, pivot.y));
	}

	collider->Create(0, 0, entireWidth, height,
		[&](Collider* other) { OnCollision(other); });
}

void Water::Impress(Vector3 pos, float width)
{
	float sx = pos.x - width / 2.f;
	float ex = pos.x + width / 2.f;

	int si = (int)(sx / this->width);
	int ei = (int)(ex / this->width);

	if (si < 0 || si >= indiceCount ||
		ei < 0 || ei >= indiceCount)
	{
		return;
	}

	constexpr float power = 1.0f;

	for (int i = si; i < ei; i++)
	{
		waterIndices[i].spd.y += power;
	}
}

void Water::ProcessWater(float dt)
{
	constexpr int	iterationCount		= 3;
	constexpr float springConstant		= 0.0095f;
	constexpr float baselineConstant	= 0.0095f;
	constexpr float dampingConstant		= 0.98f;

	for (int i = 0; i < iterationCount; i++)
	{
		for (int n = 0; n < indiceCount; n++)
		{
			waterIndex& node = waterIndices[n];

			float force				= 0;
			float force_from_left	= 0;
			float force_from_right	= 0;
			float force_to_baseline = 0;

			if (n == 0)
			{
				force_from_left = 0;
			}
			else
			{
				force_from_left = waterIndices[n - 1].y - node.y;
				force_from_left *= springConstant;
			}

			if (n == indiceCount - 1)
			{
				force_from_right = 0;
			}
			else
			{
				force_from_right = waterIndices[n + 1].y - node.y;
				force_from_right *= springConstant;
			}

			float depth_from_height = transform->position.y - node.y;
			
			force_to_baseline = baselineConstant * depth_from_height;

			force = force_from_left + force_from_right + force_to_baseline;

			node.spd.y = dampingConstant * node.spd.y + (force / node.mass);

			node.y = node.y + node.spd.y;
		}
	}
}

void Water::OnCollision(Collider * other)
{
	if (other->bTrigger)
		return;

	Impress(other->gameObject->transform->position, other->Width());
}
