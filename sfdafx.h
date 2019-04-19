#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <functional>
#include <random>
#include <string>
#include <array>
#include <thread>

#include "Enum.h"
#include "Uill.h"

using namespace std;

using Vector3 = D3DXVECTOR3;
using Vector2 = D3DXVECTOR2;

const Vector3 v3Center = Vector3(HALF_X, HALF_Y, 0);
const Vector3 v2Center = Vector2(HALF_X, HALF_Y);

const Vector3 v3Zero = Vector3(0, 0, 0);
const Vector2 v2Zero = Vector2(0, 0);

const Vector3 v3Normal = Vector3(1, 1, 1);
const Vector3 v2Normal = Vector2(1, 1);

#if DEBUG
#define CONSOLE_LOG(log) cout << log << endl;
#else
#define CONSOLE_LOG(log)
#endif

#define CHEET_MODE TRUE

#define DEVICE DXUTGetD3D9Device()
#define AC(c)	AddComponent<c>()
#define GC(c)	GetComponent<c>()
#define GO		gameObject

#define VEC(x,y) Vector3(x, y, 0)

#define UNIT_DROP_BOTTOM_LINE (800.0f)

#include "Texture.h"

#include "Manager.h"

#include "Transform.h"
#include "Renderer.h"
#include "Collider.h"
#include "Life.h"
#include "Rigidbody.h"