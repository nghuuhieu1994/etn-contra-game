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
	// Link to file Image
	//LPCSTR				m_fileName;
	// include all info of the Image
	D3DXIMAGE_INFO		m_Info;
	// Position of this texture in game
	D3DXVECTOR3*			m_Position;
	// Center of this TextureDx9
	D3DXVECTOR3*			m_Center;
	// sourceRectangle
	RectangleDx9*		m_SourceRect;
	// COLOR
	D3DCOLOR			m_Color;

	
public:
	// Cosntructor none Parameter
	CTextureDx9();

	// Constructor 2 parametor position and fileName
	CTextureDx9(D3DXVECTOR3* position, LPCSTR fileName, D3DCOLOR color);
	// constructor cpy
	CTextureDx9(const CTextureDx9* textureDx9);
	// Load texture from file
	//LPDIRECT3DTEXTURE9 LoadTextureFromeFile(LPDIRECT3DDEVICE9 _lpDirectDevice);

	void LoadTextureFromeFile(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR	fileName);
	// Return the info of this image
	D3DXIMAGE_INFO getINFO();
	// set RECT
	void setRECT(RECT* otherRECT);

	// Render this Texture
	void RenderTexture(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSprite);
	void RenderTexture(LPD3DXSPRITE _lpDSprite, RECT* SourceRectangle, D3DXVECTOR3* Location);

	~CTextureDx9();
};

#endif