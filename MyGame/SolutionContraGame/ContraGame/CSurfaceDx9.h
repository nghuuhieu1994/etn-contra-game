#ifndef __CSURFACEDX9_H__
#define __CSURFACEDX9_H__

// Use to show a big image on the screen

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "CGameLog.h"
class CSurfaceDx9
{
private:
	// LP surface to render
	LPDIRECT3DSURFACE9		m_lpSurface;
	// LP surface to make backbuffer
	LPDIRECT3DSURFACE9		m_lpBackBuffer;
public:
	// Constructor
	CSurfaceDx9();
	// Cpy Constructor
	CSurfaceDx9(const CSurfaceDx9& surface);
	// Destructor
	~CSurfaceDx9();
	// Load the data of img to m_lpSurface, get the m_lpBackBuffer
	// Step by step: Load img info --> create offscreen --> Load surface fr file --> get Backbuffer
	// ColorKey using for transparent
	void LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, D3DCOLOR ColorKey, LPCSTR fileName);
	// Show the img on the screen
	// SourceRect ---> cut a rect of img to render
	// DesRect ---> place and scale on the screen
	void RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice, RECT* SourceRect, RECT* DesRect);
	// Release all LP in this
	void UnLoadSurface();
};

#endif