#pragma once

struct ItemInfo
{
	float	frameSkip	= 0;
	float	delay		= 0;
	bool	enable		= 0;
	int		count		= 0;

	void Init();
	void Update(float dt);
	void Reset(float delay, int count = 0);

	void ItemOn(float delay);

	inline bool Use() { if (count > 0) { count--; return true; } else return false; }
};