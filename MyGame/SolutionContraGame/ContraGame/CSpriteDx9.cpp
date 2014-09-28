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
	m_Col = Sprite.m_Col;
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
void CSpriteDx9::LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, int Col, int Row, int Total, D3DXCOLOR ColorKey)
{
	m_MyTexture = new CTextureDx9();
	m_MyTexture->LoadTextureFromFile(_lpDirectDevice, fileName, ColorKey);

	m_AnimationAction = new CAnimationDx9(m_MyTexture->m_Width / Col, m_MyTexture->m_Height / Row, Col, Total);
}
void CSpriteDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation)
{
	m_AnimationAction->UpdateAnimation(gameTime, timeAnimation);
}
void CSpriteDx9::Render(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR3* Center, D3DXVECTOR3* Position, float angleRotate, eSpriteEffect SpriteEffect, D3DXVECTOR2* Scale, D3DCOLOR Color)
{
	
	//D3DXMATRIX matrixTransform;

	//D3DXMatrixIdentity(&matrixTransform);
	////m_spriteEffect(&matrixTransform, &m_listSourceRectangle.at(0));
	//float m_FlipY = 0;
	//if (SpriteEffect == eSpriteEffect::None)
	//{
	//	m_FlipY = 1.0f;
	//}

	//if (SpriteEffect == eSpriteEffect::Horizontally)
	//{
	//	m_FlipY = -1.0f;
	//}

	//D3DXMatrixScaling(&matrixTransform, m_FlipY, 1.0f, 1.0f);

	//_lpDSpriteHandle->SetTransform(&matrixTransform);

	//D3DXMATRIX matrix;
	//D3DXMatrixIdentity(&matrix);

	//matrix._22 = -1.0f;

	//matrix._41 = Camera::GetInstance()->GetMatrixTranslate()._41;
	//matrix._42 = Camera::GetInstance()->GetMatrixTranslate()._42;

	//D3DXVECTOR4 vp_pos;
	//D3DXVec3Transform(&vp_pos, Position, &matrix);

	//float halfWidth = 50 / 2;
	//float halfHeight = 50 / 2;
	//D3DXVECTOR3 p(vp_pos.x + halfWidth, vp_pos.y - halfHeight, 0);
	//D3DXVECTOR3 center(halfWidth, halfHeight, 0);
	//if (m_FlipY < 0)
	//{
	//	p.x = -p.x;
	//}

	//this->m_MyTexture->RenderTexture(_lpDSpriteHandle, this->m_AnimationAction->getSourceRect(), &center, &p, Color);
}