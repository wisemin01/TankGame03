#pragma once
#include "Singleton.h"

struct PixelMap
{
	vector<int> vecHeightMap;
	vector<int> vecRandMap;

	int mapSize = 0;
	int mapCount = 0;

	float width = 0;
	float height = 0;

	float mapWidth = 0;
	float mapHeight = 0;
};

class Collider;
class CollisionManager :
	public Singleton<CollisionManager>
{
public:
	list<Collider*> listCollider;

	PixelMap pixelMap;
public:
	CollisionManager();
	virtual ~CollisionManager();

	void FrameCheck(float dt);

	void Register(Collider* c);
	void UnRegister(Collider* c);

	void Reset();

public:

	void CreatePixelMap(Texture* multiMapBase, int count);
	void ReleasePixelMap();
	// ¹þ¾î³ª¸é true
	inline bool RangeCheck(int sector);

	COLLISION_TYPE PixelCollisionCheck(Vector3 pos);
	COLLISION_TYPE PixelGetHeight(int* pOut, int x);

	COLLISION_TYPE PixelGetLineVec(Vector3* pOut, Vector3 pos, int width);
	COLLISION_TYPE PixelGetNormalVec(Vector3* pOut, Vector3 pos, int width);
	COLLISION_TYPE PixelGetLineRot(float* pOut, Vector3 pos, int width, float spd);

	COLLISION_TYPE PixelGetHeightDepth(float* pOut, Vector3 pos, int width, const int* permit);
private:

	void SetPixelMap(Texture* singleMapBase, int index_x);
	void SetRandomMap(int kind, int count, PixelMap& refMap);
};

#define COLLISION CollisionManager::GetInstance()