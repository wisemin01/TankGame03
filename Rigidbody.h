#pragma once
#include "Component.h"
class Rigidbody :
	public Component
{
public:
	Vector3 force	 = v3Zero;
	Vector3 velocity = v3Zero;
	Vector3 damp	 = Vector3(0.95f, 0.98f, 0);

	float	mass = 1.0f;

	bool	useGravity = true;

public:
	Rigidbody();
	virtual ~Rigidbody();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;

	void AddForce(Vector3 force);
	void AddForce(float x, float y);
	void AddForce(Vector3 dir, float force);
	void AddForce(float x_dir, float y_dir, float force);

public:
	static Vector3 gravity;
};

