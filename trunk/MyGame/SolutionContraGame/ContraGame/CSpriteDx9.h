#ifndef __CSPRITE_H__
#define __CSPRITE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "CTextureDx9.h"
#include "CAnimationDx9.h"
#include "SpriteEffect.h"
#include <vector>

using namespace std;

class CSpriteDx9
{
private:
	// Hold the texture to render
	CTextureDx9*		m_MyTexture;
	// Hold the action animation
	CAnimationDx9*		m_MyAnimation;
	// Num colum in a row of this sheet image
	int					m_ColFrame;
	// Num row in a colum of this sheer image
	int					m_RowFrame;
	// Total frame in this sheet image
	int					m_TotalFrame;

	// SourceRect
	RECT*				m_SourceRectangle;
	// Center of this Texture / image
	D3DXVECTOR3*		m_Center;
	// Position to render
	D3DXVECTOR3*		m_Position;
	// Color must be 0xFFFFFFFF
	D3DXCOLOR			m_Color;

public:
	CSpriteDx9();
	CSpriteDx9(const CSpriteDx9* otherSprite);
	CSpriteDx9(const CSpriteDx9& otherSprite);
	CSpriteDx9(D3DXVECTOR3* Position, D3DCOLOR  color, int ColFrame, int RowFrame, int TotalFrame);
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	void LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName);
	void Render(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSpriteHandler);
	void Render(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSPriteHandler, SpriteEffect spriteEffect, float angleRotate, float depth);
	void Release();
};

#endif