#pragma once
#include "GameObject.h"
class ScoreInput :
	public GameObject
{
public:
	string tempString;
	string scoreString;
	string filePath;
public:
	ScoreInput();
	virtual ~ScoreInput();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Texture* tex, const string& file);

private:
	void SaveToFile();
};

