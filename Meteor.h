#pragma once
#include "GameObject.h"


class Meteor :
	public GameObject
{
public:
	Vector3 direction = v3Zero;

	float speed = 0;

	bool screenWarning = true;
	bool droping = true;
public:
	Meteor();
	virtual ~Meteor();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, Vector3 dir, float speed);

	void OnCollision(Collider* other);

private:
	void OnDeath();
};

