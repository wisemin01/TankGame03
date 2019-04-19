#include "DXUT.h"
#include "EnemyController.h"

#include "Enemy.h"

size_t EnemyController::enemyCount = 0;
size_t EnemyController::enemyKillCount = 0;


EnemyController::EnemyController()
{
	EnemyController::enemyCount = 0;
	EnemyController::enemyKillCount = 0;
}


EnemyController::~EnemyController()
{
}

void EnemyController::Init()
{
	frameSkip = 0;
	spawnDelay = 0;
}

void EnemyController::Update(float dt)
{
	frameSkip += dt;

	if (frameSkip >= spawnDelay)
	{
		if (enemyCount <= 5) {

			int		enemy_type = random<int>(ENEMY_TYPE::DEFAULT, ENEMY_TYPE::DROP_MINE);
			
			Vector3 pos		= CAMERA.vEye + Vector3(random<int>(HALF_X, WIDTH), -HALF_Y - 300, 0);
			Vector3 offset	= Vector3(random<int>(300, 500), random<int>(-200, -300), 0);
			float	speed	= random<int>(30, 35);

			InstanceEx(Enemy)(4)->Setup((ENEMY_TYPE)enemy_type, pos, offset, speed);

			frameSkip = 0.0f;
		}
	}
}

void EnemyController::Render()
{
}

void EnemyController::Destroy()
{
}

void EnemyController::Setup(float spawnDelay)
{
	this->spawnDelay = spawnDelay;
}
