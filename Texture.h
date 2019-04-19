#pragma once

struct Texture
{
public:
	virtual ~Texture();

	LPDIRECT3DTEXTURE9 pTex = NULL;
	D3DXIMAGE_INFO info;

	virtual Texture* GetImage(int count = -1) PURE;
	virtual void AddImage(const string& path, int count = 0) PURE;

	virtual int size() PURE;
};

struct SingleTexture
	: public Texture
{
	virtual ~SingleTexture();

	virtual Texture* GetImage(int count = -1) override;
	virtual void AddImage(const string& path, int count = 0) override;

	virtual int size() override;
};

struct MultiTexture 
	: public Texture
{
	virtual ~MultiTexture();

	vector<Texture*> vecTex;

	virtual Texture* GetImage(int count = -1) override;
	virtual void AddImage(const string& path, int count = 0) override;

	virtual int size() override;
};