#include "CTextureDx9.h"

CTextureDx9::CTextureDx9()
{
	m_lpTexture = 0;
}

CTextureDx9::CTextureDx9(const CTextureDx9& Texture)
{
	m_lpTexture = LPDIRECT3DTEXTURE9(Texture.m_lpTexture);
	m_Width = Texture.m_Width;
	m_Height = Texture.m_Height;
}

CTextureDx9::~CTextureDx9()
{
	UnLoadTexture();
}

void CTextureDx9::LoadTextureFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, D3DXCOLOR ColorKey)
{
	D3DXIMAGE_INFO _infoImg;
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileName, &_infoImg);
	m_Width = _infoImg.Width;
	m_Height = _infoImg.Height;

	if(FAILED(hr))
	{
		CGameLog::getInstance("CTextureDx9")->SaveError("Can't get image info from file");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		_lpDirectDevice,
		fileName,
		_infoImg.Width,
		_infoImg.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		ColorKey,
		&_infoImg,
		0,
		&m_lpTexture
		);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CTextureDx9")->SaveError("can't load texture from file");
		return;
	}
}

void CTextureDx9::Render(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR2 position, D3DXVECTOR2 Center, D3DXVECTOR2 scale, float angle, D3DCOLOR color, RECT *srcRect, float deep)
{
	D3DXVECTOR3 currentPosition(position.x, position.y, deep);//toa do trong the gioi thuc

	D3DXMATRIX oldMatrix;//ma tran luu lai phep transform cua SpriteBatch

	_lpDSpriteHandle->GetTransform(&oldMatrix);

	D3DXVECTOR2 centerScale = D3DXVECTOR2(position.x, position.y);//lay vi tri cua vat the lam tam xoay(vi vi tri cua vat la vi tri chinh giua cua vat)

	D3DXMATRIX matrixScalingRotate;//ma tran rotate, scale

	D3DXMatrixTransformation2D(&matrixScalingRotate, &centerScale, 0.0f, &scale, &Center, D3DXToRadian(angle), 0);

	D3DXMATRIX finalMatrix = matrixScalingRotate * oldMatrix;

	_lpDSpriteHandle->SetTransform(&finalMatrix);//ma tran chuyen toa do vi tri cua vat the tu the gioi thuc sang toa do trong directX de ve

	_lpDSpriteHandle->Draw(
		this->m_lpTexture,
		srcRect,
		&D3DXVECTOR3((float)(srcRect->right - srcRect->left)/2, (float)(srcRect->bottom - srcRect->top)/2, 0),
		&currentPosition,
		color);

	_lpDSpriteHandle->SetTransform(&oldMatrix);
}

void CTextureDx9::RenderTexture(LPD3DXSPRITE _lpDSpriteHandle,const RECT* sourceRect, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, D3DCOLOR Color)
{
	_lpDSpriteHandle->Draw(m_lpTexture, sourceRect, Center, Position, Color);
}

void CTextureDx9::UnLoadTexture()
{
	SAFE_RELEASE(m_lpTexture);
}