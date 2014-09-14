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
void CSpriteDx9::Render(LPD3DXSPRITE _lpDSpriteHandle, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, float angleRotate, eSpriteEffect SpriteEffect, D3DXVECTOR2* Scale, D3DCOLOR Color)
{
	D3DXMATRIX oldTrasf;
	_lpDSpriteHandle->GetTransform(&oldTrasf);
	D3DXVECTOR2 rotate;
	rotate.x = Position->x;
	rotate.y = Position->y;
	D3DXMATRIX newTransfMatrix;

	switch (SpriteEffect)
	{
	case None:
		//D3DXMatrixTransformation2D(&newTransfMatrix, &rotate, 0.0f, Scale, &rotate, angleRoate, NULL);
		break;
	case Horizontally:
		Scale->x *= -1;
		//D3DXMatrixTransformation2D(&newTransfMatrix, &rotate, 0.0f, Scale, &rotate, angleRoate, NULL);
		break;
	case Vertically:
		Scale->y *= -1;
		//D3DXMatrixTransformation2D(&newTransfMatrix, &rotate, 0.0f, Scale, &rotate, angleRoate, NULL);
		break;
	default:
		break;
	}
	D3DXMatrixTransformation2D(&newTransfMatrix, &rotate, 0.0f, Scale, &rotate, angleRotate, NULL);
	D3DXMATRIX fn = newTransfMatrix * oldTrasf;
	_lpDSpriteHandle->SetTransform(&fn);
	m_MyTexture->RenderTexture(_lpDSpriteHandle, m_AnimationAction->getSourceRect(), Center, Position, Color);
	_lpDSpriteHandle->SetTransform(&oldTrasf);
}