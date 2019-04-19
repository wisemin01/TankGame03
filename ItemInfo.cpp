#include "DXUT.h"
#include "ItemInfo.h"

void ItemInfo::Init()
{
	frameSkip = 0;
	delay = 0;
	enable = 0;
	count = 0;
}

void ItemInfo::Update(float dt)
{
	if (delay < 0)
		return;

	frameSkip += dt;

	if (frameSkip >= delay)
	{
		enable = false;
		// Reset(0, 0);
	}
}

void ItemInfo::Reset(float delay, int count)
{
	ItemInfo::frameSkip = 0;
	ItemInfo::delay = delay;
	ItemInfo::enable = false;
	ItemInfo::count = count;
}

void ItemInfo::ItemOn(float delay)
{
	ItemInfo::frameSkip = 0;
	ItemInfo::delay = delay;
	ItemInfo::enable = true;
}
