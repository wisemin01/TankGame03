#include "DXUT.h"
#include "Texture.h"

SingleTexture::~SingleTexture()
{
	SAFE_RELEASE(pTex);
}

Texture * SingleTexture::GetImage(int count)
{
	return this;
}

void SingleTexture::AddImage(const string & path, int count)
{
	if (FAILED(D3DXCreateTextureFromFileExA(DEVICE, path.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(10, 10, 10), &info, 0, &pTex)))
	{
		CONSOLE_LOG(path);
	}
}

int SingleTexture::size()
{
	return 1;
}

MultiTexture::~MultiTexture()
{
	for (auto iter : vecTex)
	{
		SAFE_DELETE(iter);
	}
}

Texture * MultiTexture::GetImage(int count)
{
	if (count == -1)
		return this;
	else
		return vecTex[count];
}

void MultiTexture::AddImage(const string & path, int count)
{
	char sz[256] = "";

	vecTex.reserve(count);

	for (int i = 1; i <= count; i++)
	{
		sprintf(sz, path.c_str(), i);

		Texture* pNew = new SingleTexture;
		pNew->AddImage(sz);

		vecTex.push_back(pNew);
	}
}

int MultiTexture::size()
{
	return vecTex.size();
}

Texture::~Texture()
{
}
