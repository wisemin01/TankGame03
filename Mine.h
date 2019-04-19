#pragma once
#include "GameObject.h"
class Mine :
	public GameObject
{
public:
	bool bDroping = false;
public:
	Mine();
	virtual ~Mine();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetupWithGround(Vector3 pos);
	void SetupWithDrop(Vector3 pos);

	void OnCollision(Collider* other);

private:
	void OnDeath();

public:
	static constexpr int permitHeight = 12;

	static void CreateMineOnGround(int startX, int count, int depthMin, int depthMax);
};

