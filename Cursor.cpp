#include "DXUT.h"
#include "Cursor.h"

int Cursor::cursorRefCount = 0;

Cursor::Cursor()
{
	cursorRefCount++;
	ShowCursor(false);
}


Cursor::~Cursor()
{
	cursorRefCount--;

	if (cursorRefCount == 0)
		ShowCursor(true);
}

void Cursor::Init()
{
	AC(Transform);
	AC(Renderer);

	renderer->SetTexture("CURSOR");
	renderer->renderType = SCREEN;
}

void Cursor::Update(float dt)
{
	transform->position = INPUT.GetMouse();
}

void Cursor::Render()
{
}

void Cursor::Destroy()
{
}
