#ifndef __CTEXTUREDX9_H__
#define __CTEXTUREDX9_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameLog.h"

class CTextureDx9
{
private:
	// LP to a texture using for render
	LPDIRECT3DTEXTURE9			m_lpTexture;
public:
	// int Width of texture
	int							m_Width;
	// int Height of texture
	int							m_Height;
	// constructor
	CTextureDx9();
	//cpy constructor
	CTextureDx9(const CTextureDx9& Texture);
	// destructor
	~CTextureDx9();
	// load texture with colorkey default = 0xff000000
	void LoadTextureFromFile(LPDIRECT3DDEVICE9 _lpDirectdevice, LPCSTR fileName, D3DXCOLOR ColorKey = 0xffff00ff);
	// render this texture to screen with default color = 0xffffff
	void RenderTexture(LPD3DXSPRITE _lpDSpriteHandle, const RECT* sourceRect, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, D3DCOLOR Color = 0xFFFFFFFF);
	// unload this texture
	void UnLoadTexture();
};

#endif