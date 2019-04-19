#pragma once
#include "Screen.h"
class ScoreScreen :
	public Screen
{
public:
	std::array<std::pair<int, string>, 3> scoreArray;
	Vector3 positionIndices[3];

	int scoreCount = 0;
	bool bRender = false;
public:
	ScoreScreen();
	virtual ~ScoreScreen();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, Texture* tex, int exit_key = VK_LBUTTON);
};

