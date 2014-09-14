#include "CTextureDx9.h"

CTextureDx9::CTextureDx9()
{
	m_lpTexture = NULL;
}

CTextureDx9::CTextureDx9(const CTextureDx9& Texture)
{
	m_lpTexture = LPDIRECT3DTEXTURE9(Texture.m_lpTexture);
}

CTextureDx9::~CTextureDx9()
{
	UnLoadTexture();
}

void CTextureDx9::LoadTextureFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, D3DXCOLOR ColorKey)
{
	D3DXIMAGE_INFO _infoImg;
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileName, &_infoImg);
	m_Width = _infoImg.Width;
	m_Height = _infoImg.Height;
	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't get image info from file");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		_lpDirectDevice,
		fileName,
		_infoImg.Width,
		_infoImg.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		ColorKey,
		&_infoImg,
		NULL,
		&m_lpTexture
		);
	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("can't load texture from file");
		return;
	}
}

void CTextureDx9::RenderTexture(LPD3DXSPRITE _lpDSpriteHandle,const RECT* sourceRect, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, D3DCOLOR Color)
{
	_lpDSpriteHandle->Draw(m_lpTexture, sourceRect, Center, Position, Color);
}

void CTextureDx9::UnLoadTexture()
{
	SAFE_RELEASE(m_lpTexture);
}