#ifndef __CSPRITEDX9_H__
#define __CSPRITEDX9_H__
#include "CGame.h"
#include "CTextureDx9.h"
#include "CAnimationDx9.h"
class CSpriteDx9
{
private:
	// contain all info of this Texture using to draw on screen
	CTextureDx9*			m_MyTexture;
	// contain all info of this animation action to make animation
	CAnimationDx9*			m_AnimationAction;
	// collum of this sheet
	int						m_Col;
	// row of this sheet
	int						m_Row;
	// total frame in this sheet
	int						m_Total;
public:
	// constructor
	CSpriteDx9();
	// copy contructor
	CSpriteDx9(const CSpriteDx9& Sprite);
	//destructor
	~CSpriteDx9();
	// update this animation action
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	// load all info about this Sprite
	void LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, int Col, int Row, int Total, D3DXCOLOR ColorKey = 0xFF000000);
	// draw this sprite to screen
	void Render(LPD3DXSPRITE _lpDSpriteHandle, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, float angleRotate = 0, eSpriteEffect SpriteEffect = eSpriteEffect::None, D3DXVECTOR2* Scale = new D3DXVECTOR2(1, 1), D3DCOLOR Color = 0xffffffff);
	void Release();
};

#endif