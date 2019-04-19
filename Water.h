#pragma once
#include "GameObject.h"
class Water :
	public GameObject
{
private:
	struct waterIndex : Vector2
	{
		Vector2 spd = v2Zero;
		float mass = 1.0f;

		waterIndex(float x, float y) : Vector2(x, y) {}
	};
public:
	vector<waterIndex> waterIndices;
	Texture* waterTex = nullptr;

	int indiceCount = 0;
	
	float width = 0;
	float height = 0;

	float entireWidth = 0;
	float sinIndex = 0;

public:
	Water();
	virtual ~Water();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pivot, int indiceCnt);
	void Impress(Vector3 pos, float width);

private:
	void ProcessWater(float dt);

	void OnCollision(Collider* other);
};

