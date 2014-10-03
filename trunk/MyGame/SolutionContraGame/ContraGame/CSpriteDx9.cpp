#include "CSpriteDx9.h"

CSpriteDx9::CSpriteDx9()
{
	m_MyTexture = NULL;
	m_AnimationAction = NULL;
}

CSpriteDx9::CSpriteDx9(const CSpriteDx9& Sprite)
{
	m_MyTexture = new CTextureDx9(*Sprite.m_MyTexture);
	m_AnimationAction = new CAnimationDx9(*Sprite.m_AnimationAction);
	m_Column = Sprite.m_Column;
	m_Row = Sprite.m_Row;
	m_Total = Sprite.m_Total;
}

CSpriteDx9::~CSpriteDx9()
{
	this->Release();
}

void CSpriteDx9::Release()
{
	m_MyTexture->UnLoadTexture();
	m_AnimationAction->Release();
}

void CSpriteDx9::LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, int Column, int Row, int Total, D3DXCOLOR TransparentColor)
{
	m_MyTexture = new CTextureDx9();
	m_MyTexture->LoadTextureFromFile(_lpDirectDevice, fileName, TransparentColor);

	m_AnimationAction = new CAnimationDx9(m_MyTexture->m_Width / Column, m_MyTexture->m_Height / Row, Column, Total);
}

void CSpriteDx9::UpdateAnimation(int timeAnimation)
{
	m_AnimationAction->UpdateAnimation(timeAnimation);
}

CAnimationDx9* CSpriteDx9::getAnimation()
{
	return m_AnimationAction;
}

void CSpriteDx9::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, eSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color)
{
	/*D3DXVECTOR2 m_vOrigin = D3DXVECTOR2(position.x + m_AnimationAction->GetFrameSize().x/2,
										position.y + m_AnimationAction->GetFrameSize().y/2);*/
	D3DXVECTOR2 m_vOrigin = D3DXVECTOR2(position.x, position.y);
	if(m_MyTexture != 0)
	{
		if(effect == eSpriteEffect::None)
		{
			m_MyTexture->Render(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
		}
		else
		{
			if(effect == eSpriteEffect::Horizontally)
			{
				m_MyTexture->Render(spriteHandle, position, m_vOrigin, D3DXVECTOR2(-scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
			}
			else
			{
				if(effect == eSpriteEffect::Vertically)
				{
					m_MyTexture->Render(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
				}
			}
		}
	}
}