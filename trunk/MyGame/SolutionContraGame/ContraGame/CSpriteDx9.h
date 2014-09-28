#ifndef __CSPRITEDX9_H__
#define __CSPRITEDX9_H__
#include "CGame.h"
#include "CTextureDx9.h"
#include "CAnimationDx9.h"
class CSpriteDx9
{
private:
	
	CTextureDx9*			m_MyTexture;
	
	CAnimationDx9*			m_AnimationAction;
	
	int						m_Col;
	
	int						m_Row;
	
	int						m_Total;
public:
	
	CSpriteDx9();
	
	CSpriteDx9(const CSpriteDx9& Sprite);
	
	~CSpriteDx9();
	void LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, int Col, int Row, int Total, D3DXCOLOR ColorKey = 0xFF000000);
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	void Render(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR3* Center, D3DXVECTOR3* Position, float angleRotate = 0, eSpriteEffect SpriteEffect = eSpriteEffect::None, D3DXVECTOR2* Scale =  &D3DXVECTOR2(1, 1), D3DCOLOR Color = 0xffffffff);
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, eSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color = 0xffff0000)
	{
		D3DXVECTOR2 m_vOrigin = D3DXVECTOR2(position.x + m_AnimationAction->GetFrameSize().x/2,
											position.y + m_AnimationAction->GetFrameSize().y/2);
		if(m_MyTexture != 0)
		{
			if(effect == eSpriteEffect::None)
			{
				m_MyTexture->RenderTexture(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
			}
			else
			{
				if(effect == eSpriteEffect::Horizontally)
				{
					m_MyTexture->RenderTexture(spriteHandle, position, m_vOrigin, D3DXVECTOR2(-scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
				}
				else
				{
					if(effect == eSpriteEffect::Vertically)
					{
						m_MyTexture->RenderTexture(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
					}
				}
			}
		}
	}
	void Release();
};

#endif