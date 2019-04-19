#pragma once
#include "GameObject.h"
class SavePoint :
	public GameObject
{
public:
	bool bPassed = false;
public:
	SavePoint();
	virtual ~SavePoint();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos);

	void OnCollision(Collider* other);

public:
	static void CreateSavePoints(int startX, int count);
};

