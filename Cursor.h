#pragma once
#include "GameObject.h"
class Cursor :
	public GameObject
{
public:

public:
	Cursor();
	virtual ~Cursor();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

public:
	static int cursorRefCount;
};

