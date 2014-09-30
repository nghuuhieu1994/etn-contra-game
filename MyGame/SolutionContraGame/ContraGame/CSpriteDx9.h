#ifndef __CSPRITEDX9_H__
#define __CSPRITEDX9_H__

#include "CGlobal.h"
#include "CTextureDx9.h"
#include "CAnimationDx9.h"

class CSpriteDx9
{
private:
	CAnimationDx9*			m_AnimationAction;

	CTextureDx9*			m_MyTexture;	
	
	int						m_Col;
	
	int						m_Row;
	
	int						m_Total;

	eSpriteEffect			m_SpriteEffect;

	float					m_Scale;
	float					m_Rotate;
	
	D3DXVECTOR2				m_RotateCenter;
	D3DXVECTOR2				m_ScaleCenter;
public:
	
							CSpriteDx9();
	
							CSpriteDx9(const CSpriteDx9& Sprite);
	
							~CSpriteDx9();

	CAnimationDx9*			getAnimation();

	void					LoadContent(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR fileName, int Col, int Row, int Total, D3DXCOLOR TransparentColor = 0xFF000000);

	void					UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	
	void					Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, eSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color = 0xffffffff);
	
	void					Release();
};

#endif