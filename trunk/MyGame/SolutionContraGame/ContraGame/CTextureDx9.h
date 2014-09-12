#ifndef __CTEXTURE_H__
#define	__CTEXTURE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "VectorDx9.h"
#include "RectangleDx9.h"
#include "VectorDx9.h"

class CTextureDx9
{
private:	
	// Lp to an instance of interface D3DTexture
	LPDIRECT3DTEXTURE9	m_lpDTexture;
	// include all info of the Image
	D3DXIMAGE_INFO		m_Info;
	
public:
	// Cosntructor none Parameter
	CTextureDx9();
	// constructor cpy
	CTextureDx9(const CTextureDx9* textureDx9);
	// constructor cpy
	CTextureDx9(const CTextureDx9& textureDx9);
	// Load texture from file
	void LoadTextureFromFile(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR	fileName);
	// Return the info of this image
	D3DXIMAGE_INFO getINFO();
	// Render this Texture
	void RenderTexture(LPD3DXSPRITE _lpDSprite, RECT* SourceRectangle,D3DXVECTOR3* Center, D3DXVECTOR3* Position, D3DXCOLOR Color);
	// Unload Texture
	void UnLoadTexture();
	// Destructor
	~CTextureDx9();
};

#endif