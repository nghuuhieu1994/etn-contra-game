#include "CSpriteDx9.h"
#include "CGameLog.h"

/*
CSpriteDx9::CSpriteDx9()
{

}
CSpriteDx9::CSpriteDx9(D3DXVECTOR3* Position, LPCSTR fileName, D3DCOLOR color, int ColFrame, int RowFrame, int TotalFrame)
{

}
void CSpriteDx9::LoadTexture(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName)
{
	
	this->m_animation = new CAnimationDx9();
	
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileName, &m_Info);
	if (FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't get Image info frome file");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		_lpDirectDevice,
		fileName,
		m_Info.Width,
		m_Info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),//use color ( 255, 255, 0, 255) to transparent texture
		&m_Info,
		NULL,
		&this->m_lpDTexture);

	if (FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't Create Texture from file");
		return;
	}

}

CSpriteDx9::CSpriteDx9(const CSpriteDx9* otherSprite)
{
	this->m_Texture = new CTextureDx9(otherSprite->m_Texture);
	this->m_MyAnimation = new CAnimationDx9(otherSprite->m_MyAnimation);
}

void CSpriteDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation)
{
	this->m_animation->UpdateAnimation(gameTime, timeAnimation); 
}

void CSpriteDx9::InitializeSpriteData(int frameWidth, int frameHeight, int sheetColumn, int sheetRow, int totalFrameOfSprite)
{
	this->m_totalFrameOfSprite = totalFrameOfSprite;


	for (int i = 0; i < totalFrameOfSprite; i++)
	{
		RECT tempRect;
		tempRect.top = (i / sheetColumn) * frameHeight;
		tempRect.left = (i % sheetColumn) * frameWidth;
		tempRect.bottom = frameHeight + tempRect.top;
		tempRect.right = frameWidth + tempRect.left;
		m_listSourceRectangle.push_back(tempRect);
	}
}

CAnimationDx9* CSpriteDx9::getAnimation()
{
	return this->m_animation;
}

void CSpriteDx9::Render(LPD3DXSPRITE _SpriteBatch, D3DXVECTOR3* _Location)
{
	DWORD AlphaValue;
	AlphaValue = D3DCOLOR_ARGB(255, 255, 255, 255);
	_SpriteBatch->Draw(
		this->m_lpDTexture,
		&m_listSourceRectangle.at(m_animation->GetCurrentFrameIndex()),
		NULL,
		_Location,
		AlphaValue);
}

void CSpriteDx9::Render(LPD3DXSPRITE spriteBatch, D3DXVECTOR3* location, void(*spriteEffect)(D3DXMATRIX*, RECT* frameRect))
{
	D3DXMATRIX matrixTransform;

	D3DXMatrixIdentity(&matrixTransform);
	spriteEffect(&matrixTransform, &m_listSourceRectangle.at(0));

	spriteBatch->SetTransform(&matrixTransform);
	
	DWORD AlphaValue;
	AlphaValue = D3DCOLOR_ARGB(255, 255, 255, 255);
	spriteBatch->Draw(
		this->m_lpDTexture,
		&m_listSourceRectangle.at(m_animation->GetCurrentFrameIndex()),
		NULL,
		location,
		AlphaValue);
}
*/

