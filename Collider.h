#pragma once
#include "Component.h"


class Collider :
	public Component
{
public:
	bool bTrigger = false;
public:
	RECT range;
	Vector3 offset;
	
	function<void(Collider* other)> onCollisionFunc;
public:
	Collider();
	virtual ~Collider();

	void Create(float l, float t, float r, float b, function<void(Collider*)> func);
	void Create(float w, float h, function<void(Collider*)> func);
	void CreateWithTexture(Texture* tex, function<void(Collider*)> func);

	virtual void Init() override;
	virtual void Destroy() override;

	RECT GetWorldRange();

	size_t Width();
	size_t Height();

	void resize(float w, float h);
	void resize(float l, float t, float r, float b);
	void resize(Texture* tex);

	bool CompareTag(const string& tag);
private:
	friend class CollisionManager;

	void OnCollision(Collider* other);

};

