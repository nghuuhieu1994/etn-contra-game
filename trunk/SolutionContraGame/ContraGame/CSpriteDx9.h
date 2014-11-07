#ifndef __CSPRITEDX9_H__
#define __CSPRITEDX9_H__


#include "CTextureDx9.h"
#include "CAnimationDx9.h"
#include "ESpriteEffect.h"

class CSpriteDx9
{
private:

	CAnimationDx9*			m_AnimationAction;
	CTextureDx9*			m_MyTexture;

	int						m_Column;

	int						m_Row;

	int						m_Total;

	ESpriteEffect			m_SpriteEffect;

	float					m_Scale;
	float					m_Rotate;

public:
	CAnimationDx9*			getAnimationAction()const { return m_AnimationAction; }
	CTextureDx9*			getMyTexture()const { return m_MyTexture; }
	ESpriteEffect			getSpriteEffect()const { return m_SpriteEffect; }
	float					getRotate()const { return m_Rotate; }
	float					getScale()const { return m_Scale; }
	int						getColumn()const { return m_Column; }
	int						getRow()const { return m_Row; }
	int						getTotal()const { return m_Total; }
	void					setAnimationAction(CAnimationDx9* _animationaction){ m_AnimationAction = _animationaction; }
	void					setColumn(int _column){ m_Column = _column; }
	void					setMyTexture(CTextureDx9* _mytexture){ m_MyTexture = _mytexture; }
	void					setRotate(float _rotate){ m_Rotate = _rotate; }
	void					setRow(int _row){ m_Row = _row; }
	void					setScale(float _scale){ m_Scale = _scale; }
	void					setSpriteEffect(ESpriteEffect _spriteeffect){ m_SpriteEffect = _spriteeffect; }
	void					setTotal(int _total){ m_Total = _total; }

							CSpriteDx9();
							CSpriteDx9(const CSpriteDx9& Sprite);
							~CSpriteDx9();
	CAnimationDx9*			getAnimation();
	void					LoadContent(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR fileName, int Column, int Row, int Total, D3DXCOLOR TransparentColor = 0xFFFF00FF);
	void					Release();
	void					Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color = 0xffffffff);
	void					RenderAtFrame(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color, int frameIndex);
	void					UpdateAnimation(int timeAnimation);
};

#endif