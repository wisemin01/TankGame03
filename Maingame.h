#pragma once


class Maingame
{
public:

public:
	Maingame();
	virtual ~Maingame();

	void Init();
	void Update(float dt);
	void Render();
	void Destroy();

	void OnReset();
	void OnLost();
};

