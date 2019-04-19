#pragma once
#include "GameObject.h"

class Player;
class PlayerController :
	public GameObject
{
public:
	Player * player		= nullptr;

	FLOAT anyTime		= 300.0f;
	FLOAT gameProgress	= 0.0f;

	string drawString[2];
public:
	Texture* pHeart		= nullptr;
	Texture* pItem		= nullptr;
	Texture* pProgress	= nullptr;
	Texture* pPlayerInvinc = nullptr;
	Texture* pPlayerSpeedup = nullptr;

	int* nowStageScore  = nullptr;
	bool stageEnd		= false;
public:
	PlayerController();
	virtual ~PlayerController();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

public:
	void Spawn();
private:
	void DrawScreen();
	void DrawHeart();
	void DrawItem();
	void DrawProgress();

	void ProcessScore();
public:
	static int playerHeart;
	static Vector3 playerRespawn;

	static int stage1Score;
	static int stage2Score;

	static bool stageClear;
};

