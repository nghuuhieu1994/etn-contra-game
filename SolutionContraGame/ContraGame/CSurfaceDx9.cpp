#include "CSurfaceDx9.h"

CSurfaceDx9::CSurfaceDx9()
{
	m_lpSurface = 0;
	m_lpBackBuffer = 0;
}
CSurfaceDx9::CSurfaceDx9(const CSurfaceDx9& surface)
{
	m_lpSurface = LPDIRECT3DSURFACE9(surface.m_lpSurface);
	m_lpBackBuffer = LPDIRECT3DSURFACE9(surface.m_lpSurface);
}
CSurfaceDx9::~CSurfaceDx9()
{
	//UnLoadSurface();
}
void CSurfaceDx9::UnLoadSurface()
{
	SAFE_RELEASE(m_lpSurface);
	SAFE_RELEASE(m_lpBackBuffer);
}
void CSurfaceDx9::LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, D3DCOLOR ColorKey, LPCSTR fileName)
{
	D3DXIMAGE_INFO _infoImage;
	HRESULT hr;

	hr = D3DXGetImageInfoFromFile(fileName, &_infoImage);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CSurfaceDx9")->SaveError("Can't get image info from file");
		return;
	}

	hr = _lpDirectDevice->CreateOffscreenPlainSurface(_infoImage.Width, _infoImage.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_lpSurface, 0);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CSurfaceDx9")->SaveError("Can't create off screen surface");
		return;
	}

	hr = D3DXLoadSurfaceFromFile(
		m_lpSurface,
		0,
		0,
		fileName,
		0,
		D3DX_DEFAULT,
		ColorKey,
		0);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CSurfaceDx9")->SaveError("Can't load surface from file");
		return;
	}

	hr = _lpDirectDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_lpBackBuffer);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CSurfaceDx9")->SaveError("Can't get Backbuffer");
		return;
	}
}


void CSurfaceDx9::RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice, RECT* SourceRect, RECT* DesRect)
{
	_lpDirectDevice->StretchRect(
		m_lpSurface,
		SourceRect,
		m_lpBackBuffer,
		DesRect,
		D3DTEXF_NONE);
}