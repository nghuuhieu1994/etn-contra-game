#include "CTextureDx9.h"
#include "CGameLog.h"

CTextureDx9::CTextureDx9()
{
	m_lpDTexture = NULL;
}

CTextureDx9::CTextureDx9(const CTextureDx9* textureDx9)
{
	SAFE_RELEASE(m_lpDTexture);

	this->m_lpDTexture = LPDIRECT3DTEXTURE9(textureDx9->m_lpDTexture);
	this->m_Info = textureDx9->m_Info;
}

CTextureDx9::CTextureDx9(const CTextureDx9& textureDx9)
{
	SAFE_RELEASE(m_lpDTexture);
	this->m_lpDTexture = LPDIRECT3DTEXTURE9(textureDx9.m_lpDTexture);
	this->m_Info = textureDx9.m_Info;
}

void CTextureDx9::LoadTextureFromFile(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR	fileName)
{
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileName, &m_Info);
	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't get Image info frome file");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		lpDirectDevice,
		fileName,
		m_Info.Width,
		m_Info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,0,255),//use color ( 255, 255, 0, 255) to transparent texture
		&m_Info,
		NULL,
		&this->m_lpDTexture);

	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't Create Texture from file");
		return;
	}
}

D3DXIMAGE_INFO CTextureDx9::getINFO()
{
	return m_Info;
}

void CTextureDx9::RenderTexture(LPD3DXSPRITE _lpDSpriteHandle, RECT* SourceRectangle, D3DXVECTOR3* Center, D3DXVECTOR3* Position, D3DXCOLOR Color)
{
	_lpDSpriteHandle->Draw(m_lpDTexture, SourceRectangle, Center, Position, Color);
}

void CTextureDx9::UnLoadTexture()
{
	SAFE_RELEASE(m_lpDTexture);
}

CTextureDx9::~CTextureDx9()
{
	UnLoadTexture();
}