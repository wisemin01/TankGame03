#include "DXUT.h"
#include "CollisionManager.h"

#include "GameObject.h"
#include "Collider.h"

#define CHECK_COLOR D3DCOLOR_ARGB(255, 0, 0, 0)

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	Reset();
}

void CollisionManager::FrameCheck(float dt)
{
	if (listCollider.size() < 2)
		return;

	auto end = std::prev(listCollider.end(), 1);

	for (auto iter = listCollider.begin(); iter != end; iter++)
	{
		for (auto iter2 = std::next(iter, 1); iter2 != listCollider.end(); iter2++)
		{
			Collider *& c1 = (*iter);
			Collider *& c2 = (*iter2);

			if (c1->gameObject == c2->gameObject)
				continue;

			RECT * r1 = &c1->GetWorldRange();
			RECT * r2 = &c2->GetWorldRange();

			RECT r;

			if (IntersectRect(&r, r1, r2))
			{
				c1->OnCollision(c2);
				c2->OnCollision(c1);
			}
		}
	}
}

void CollisionManager::Register(Collider * c)
{
	listCollider.push_back(c);
}

void CollisionManager::UnRegister(Collider * c)
{
	listCollider.remove(c);
}

void CollisionManager::Reset()
{
	listCollider.clear();
}

void CollisionManager::CreatePixelMap(Texture * multiMapBase, int count)
{
	// MEMBER INIT
	pixelMap.mapCount	= count;
	pixelMap.width		= multiMapBase->GetImage(0)->info.Width;
	pixelMap.height		= multiMapBase->GetImage(0)->info.Height;

	pixelMap.mapWidth	= pixelMap.width * count;
	pixelMap.mapHeight	= pixelMap.height;

	// LIST CLEAR
	pixelMap.vecRandMap.clear();
	pixelMap.vecHeightMap.clear();

	// SET RANDOM MAP
	SetRandomMap(multiMapBase->size() - 1, count, pixelMap);

	pixelMap.vecHeightMap.resize(pixelMap.mapWidth, pixelMap.height);

	for (int i = 0; i < count; i++)
	{
		SetPixelMap(multiMapBase->GetImage(pixelMap.vecRandMap[i]),
			i * pixelMap.width);
	}
}

void CollisionManager::ReleasePixelMap()
{
	pixelMap.vecHeightMap.clear();
	pixelMap.vecRandMap.clear();
}

inline bool CollisionManager::RangeCheck(int sector)
{
	if (pixelMap.vecHeightMap.size() <= sector ||
		sector < 0)
		return true;
	else return false;
}

COLLISION_TYPE  CollisionManager::PixelCollisionCheck(Vector3 pos)
{
	if (RangeCheck(pos.x))
		return OUTOF_RANGE;

	if (pos.y >= pixelMap.vecHeightMap[(int)pos.x])
		return ON_COLLISION;
	else
		return NONE_COLLISION;
}

COLLISION_TYPE CollisionManager::PixelGetHeight(int* pOut, int x)
{
	if (RangeCheck(x))
		return OUTOF_RANGE;

	*pOut = pixelMap.vecHeightMap[x];

	if (*pOut >= pixelMap.height)
		return NONE_COLLISION;
	else
		return SUCCESS;
}


COLLISION_TYPE CollisionManager::PixelGetLineVec(Vector3 * pOut, Vector3 pos, int width)
{
	if (RangeCheck(pos.x + width / 2) || RangeCheck(pos.x - width / 2))
		return OUTOF_RANGE;

	int rY, lY;

	PixelGetHeight(&rY, pos.x + width / 2);
	PixelGetHeight(&lY, pos.x - width / 2);

	Vector3 right = Vector3(pos.x + width / 2, rY, 0);
	Vector3 left  = Vector3(pos.x - width / 2, lY, 0);

	Vector3 line = right - left;

	D3DXVec3Normalize(pOut, &line);

	return SUCCESS;
}

COLLISION_TYPE CollisionManager::PixelGetNormalVec(Vector3 * pOut, Vector3 pos, int width)
{
	Vector3 line;

	COLLISION_TYPE hr;

	hr = PixelGetLineVec(&line, pos, width);

	if (hr == SUCCESS)
	{
		Vector3 normal = Vector3(line.y, -line.x, 0);

		if (normal.y > 0)
			normal *= -1;

		*pOut = normal;

		return SUCCESS;
	}
	else
		return hr;
}

COLLISION_TYPE CollisionManager::PixelGetLineRot(float * pOut, Vector3 pos, int width, float spd)
{
	if (RangeCheck(pos.x))
		return OUTOF_RANGE;

	Vector3 line;
	PixelGetLineVec(&line, pos, width);

	if (PixelCollisionCheck(pos) == ON_COLLISION)
	{
		Lerp(*pOut, atan2f(line.y, line.x), spd);
	}
	else
	{
		Lerp(*pOut, 0.0f, spd * 0.33f);
	}
}


COLLISION_TYPE CollisionManager::PixelGetHeightDepth(float * pOut, Vector3 pos, int width, const int * permit)
{
	int return_type = 0;

	if (RangeCheck(pos.x - width / 2.f) || RangeCheck(pos.x + width / 2.f))
		return_type |= OUTOF_RANGE;
	else {
		constexpr float errorDepth = 20;

		float rightX = pos.x + width / 2.f - errorDepth;
		
		float leftX = pos.x - width / 2.f + errorDepth;
		
		*pOut = pos.y - pixelMap.vecHeightMap[rightX];

		if (*pOut > *permit)
		{
			return_type |= MOVELOCK_RIGHT;
		}

		*pOut = pos.y - pixelMap.vecHeightMap[leftX];

		if (*pOut > *permit)
		{
			return_type |= MOVELOCK_LEFT;
		}
	}

	return (COLLISION_TYPE)return_type;
}

void CollisionManager::SetPixelMap(Texture * singleMapBase, int index_x)
{
	D3DLOCKED_RECT lockRect;

	if (FAILED(singleMapBase->pTex->LockRect(0, &lockRect, NULL, D3DLOCK_DISCARD)))
	{
		singleMapBase->pTex->UnlockRect(0);
		return;
	}

	DWORD* dwList = (DWORD*)lockRect.pBits;

	for (int x = index_x; x < index_x + pixelMap.width; x++)
	{
		for (int y = 0; y < pixelMap.height; y++)
		{
			DWORD colorBit = dwList[(int)(y * pixelMap.width + x)];

			if (colorBit == CHECK_COLOR) {
				pixelMap.vecHeightMap[x] = min(pixelMap.vecHeightMap[x], y);
			}
		}
	}

	singleMapBase->pTex->UnlockRect(0);
	return;
}

void CollisionManager::SetRandomMap(int kind, int count, PixelMap & refMap)
{
	refMap.vecRandMap.resize(count);

	for (int i = 0; i < count; i++)
	{
		refMap.vecRandMap[i] = random(0, kind);
	}
}
