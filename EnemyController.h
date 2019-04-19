#pragma once
#include "GameObject.h"
class EnemyController :
	public GameObject
{
private:
	float frameSkip = 0;
	float spawnDelay = 0;

public:
	EnemyController();
	virtual ~EnemyController();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(float spawnDelay);

public:
	static size_t enemyCount;
	static size_t enemyKillCount;
};

