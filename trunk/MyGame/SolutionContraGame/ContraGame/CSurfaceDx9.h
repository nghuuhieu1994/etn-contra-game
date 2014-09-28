#ifndef __CSURFACEDX9_H__
#define __CSURFACEDX9_H__



#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "CGameLog.h"
class CSurfaceDx9
{
private:
	
	LPDIRECT3DSURFACE9		m_lpSurface;
	
	LPDIRECT3DSURFACE9		m_lpBackBuffer;
public:
	
	CSurfaceDx9();
	
	CSurfaceDx9(const CSurfaceDx9& surface);
	
	~CSurfaceDx9();
	
	
	
	void LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, D3DCOLOR ColorKey, LPCSTR fileName);
	
	
	
	void RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice, RECT* SourceRect, RECT* DesRect);
	
	void UnLoadSurface();
};

#endif