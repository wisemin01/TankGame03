#pragma once
#include "Singleton.h"

struct Texture;
class CSoundManager;
class CSound;
struct Texture;

class ResourceManager :
	public Singleton<ResourceManager>
{
public:
	LPD3DXSPRITE pSprite;

	map<string, Texture*> mapTexture;
	map<string, CSound*> mapSound;

	CSoundManager* pSMgr;

	INT iRenderType;
public:
	ResourceManager();
	virtual ~ResourceManager();

	Texture* AddTexture(const string& key, const string& path, int count = 0);
	Texture* GetTexture(const string& key, int count = -1);

	void SetTransform(Vector3 pos, Vector3 scale, float rot);

	void Draw(Texture* pTex, Vector3 vCenter, DWORD dwColor);
	void RectDraw(Texture* pTex, const RECT& rc, Vector3 vCenter, DWORD dwColor);

	void DrawString(const string& str, Vector3 pos, int size, DWORD dwColor);

	void AddSound(const string& key, const wstring& path);
	void SoundPlay(const string& key, int flag);
	void DuplicatePlay(const string& key);
	void SoundStop(const string& key);

	void SetRenderType(int type) { iRenderType = type; }

	void ResetTex();
	void ResetSound();

	void OnReset();
	void OnLost();

	void Begin();
	void End();
};

#define RESOURCE ResourceManager::GetInstance()

#define GETTEX RESOURCE.GetTexture
#define ADDTEX RESOURCE.AddTexture