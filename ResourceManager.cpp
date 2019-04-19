#include "DXUT.h"
#include "ResourceManager.h"

#include "SDKsound.h"

#pragma comment(lib, "dsound.lib")

ResourceManager::ResourceManager()
{
	D3DXCreateSprite(DEVICE, &pSprite);

	pSMgr = new CSoundManager;
	pSMgr->Initialize(DXUTGetHWND(), 2);
}


ResourceManager::~ResourceManager()
{
	ResetTex();
	ResetSound();

	SAFE_DELETE(pSMgr);
	SAFE_RELEASE(pSprite);
}

Texture * ResourceManager::AddTexture(const string & key, const string & path, int count)
{
	auto f = mapTexture.find(key);

	if (f == mapTexture.end())
	{
		Texture* pNew;

		if (count == 0)
			pNew = new SingleTexture;
		else
			pNew = new MultiTexture;

		pNew->AddImage(path, count);

		mapTexture.insert(make_pair(key, pNew));
		return pNew;
	}

	return f->second;
}

Texture * ResourceManager::GetTexture(const string & key, int count)
{
	auto f = mapTexture.find(key);

	if (f != mapTexture.end())
	{
		return f->second->GetImage(count);
	}
	return nullptr;
}

void ResourceManager::SetTransform(Vector3 pos, Vector3 scale, float rot)
{
	D3DXMATRIX w, s, r, t;

	Vector3 v = pos - (iRenderType == SCROLL ? (CAMERA.vEye - v3Center) : v3Zero);

	D3DXMatrixTranslation(&t, v.x, v.y, 0);
	D3DXMatrixScaling(&s, scale.x, scale.y, 0);
	D3DXMatrixRotationZ(&r, rot);

	w = s * r * t;

	pSprite->SetTransform(&w);
}

void ResourceManager::Draw(Texture * pTex, Vector3 vCenter, DWORD dwColor)
{
	pSprite->Draw(pTex->pTex, NULL, &vCenter, NULL, dwColor);
}

void ResourceManager::RectDraw(Texture * pTex, const RECT & rc, Vector3 vCenter, DWORD dwColor)
{
	pSprite->Draw(pTex->pTex, &rc, &vCenter, NULL, dwColor);
}

void ResourceManager::DrawString(const string & str, Vector3 pos, int size, DWORD dwColor)
{
	LPD3DXFONT font;
	D3DXMATRIX mat;
	
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	D3DXCreateFontA(DEVICE, size, 0, FW_HEAVY, 1, 0,
		HANGUL_CHARSET, 0, 0, 0, "¸¼Àº °íµñ", &font);

	pSprite->SetTransform(&mat);
	font->DrawTextA(pSprite, str.c_str(), str.size(), NULL, DT_NOCLIP, dwColor);

	SAFE_RELEASE(font);
}

void ResourceManager::AddSound(const string & key, const wstring & path)
{
	auto f = mapSound.find(key);

	if (f == mapSound.end())
	{
		CSound* pNew;

		pSMgr->Create(&pNew, (LPWSTR)path.c_str());
		mapSound.insert(make_pair(key, pNew));
	}
}

void ResourceManager::SoundPlay(const string & key, int flag)
{
	mapSound[key]->Reset();
	mapSound[key]->Play(0, flag);
}

void ResourceManager::DuplicatePlay(const string & key)
{
	LPDIRECTSOUNDBUFFER pBuffer;

	pSMgr->GetDirectSound()->DuplicateSoundBuffer(mapSound[key]->GetBuffer(0), &pBuffer);

	pBuffer->SetCurrentPosition(0);
	pBuffer->Play(0, 0, 0);
}

void ResourceManager::SoundStop(const string & key)
{
	mapSound[key]->Stop();
}

void ResourceManager::ResetTex()
{
	for (auto iter : mapTexture)
	{
		SAFE_DELETE(iter.second);
	}
	mapTexture.clear();
}

void ResourceManager::ResetSound()
{
	for (auto iter : mapSound)
	{
		SAFE_DELETE(iter.second);
	}
	mapSound.clear();
}

void ResourceManager::OnReset()
{
	pSprite->OnResetDevice();
}

void ResourceManager::OnLost()
{
	pSprite->OnLostDevice();
}

void ResourceManager::Begin()
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void ResourceManager::End()
{
	pSprite->End();
}
