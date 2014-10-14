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
	
	int						m_Column;
	
	int						m_Row;
	
	int						m_Total;

	ESpriteEffect			m_SpriteEffect;

	float					m_Scale;
	float					m_Rotate;
	
public:
	
	void					setAnimationAction(CAnimationDx9* _animationaction){ m_AnimationAction = _animationaction; }
	CAnimationDx9*			getAnimationAction()const { return m_AnimationAction; }

	void					setMyTexture(CTextureDx9* _mytexture){ m_MyTexture = _mytexture; }
	CTextureDx9*			getMyTexture()const { return m_MyTexture; }

	void					setColumn(int _column){ m_Column = _column; }
	int						getColumn()const { return m_Column; }

	void					setRow(int _row){ m_Row = _row; }
	int						getRow()const { return m_Row; }

	void					setTotal(int _total){ m_Total = _total; }
	int						getTotal()const { return m_Total; }

	void					setSpriteEffect(ESpriteEffect _spriteeffect){ m_SpriteEffect = _spriteeffect; }
	ESpriteEffect			getSpriteEffect()const { return m_SpriteEffect; }

	void					setScale(float _scale){ m_Scale = _scale; }
	float					getScale()const { return m_Scale; }

	void					setRotate(float _rotate){ m_Rotate = _rotate; }
	float					getRotate()const { return m_Rotate; }

							CSpriteDx9();
	
							CSpriteDx9(const CSpriteDx9& Sprite);
	
							~CSpriteDx9();

	CAnimationDx9*			getAnimation();

	void					LoadContent(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR fileName, int Column, int Row, int Total, D3DXCOLOR TransparentColor = 0xFFFF00FF);

	void					UpdateAnimation(int timeAnimation);
	
	void					Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color = 0xffffffff);
	void					RenderAtFrame(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color, int frameIndex);
	void					Release();
};

#endif