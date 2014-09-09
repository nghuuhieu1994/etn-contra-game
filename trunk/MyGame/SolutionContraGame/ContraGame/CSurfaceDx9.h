#ifndef __CSURFACE_H__
#define __CSURFACE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "RectangleDx9.h"
#include "VectorDx9.h"
class CSurfaceDx9;

class CSurfaceDx9
{
private:
	// LP surface to render something
	LPDIRECT3DSURFACE9		m_lpDSurface;
	// LP surface to make backbff
	LPDIRECT3DSURFACE9		m_lpDBackBuffer;
	// Link to file Image
	LPCSTR					m_fileName;
	// include all infomation of the image
	D3DXIMAGE_INFO			m_Info;
	// Position of the surface
	D3DXVECTOR3*				m_Position;
	// SourceRect to render
	RectangleDx9*			m_SourceRect;
	// DestREct to render
	RectangleDx9*			m_DestRect;
	// Create Offscreen Surface
	bool	CreateOffScreenSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice);
	// Load surface
	bool	LoadSurfaceFromFile();
public:
	// constructor none parametor
	CSurfaceDx9();
	// constructor 2 parametor Position and fileName
	CSurfaceDx9(D3DXVECTOR3* position, LPCSTR  fileName);
	// constructor copi
	CSurfaceDx9(const  CSurfaceDx9* surfaceDx9);
	// get sourceRect
	RectangleDx9* getSourceRect();
	// get DestRect
	RectangleDx9* getDestRect();
	// set SourceRect
	void setSourceRect(RectangleDx9 sorceRect);
	// set DestRect
	void setDestRect(RectangleDx9 destRect);
	// Do all thing to Load surface
	LPDIRECT3DSURFACE9 LoadSurface(LPDIRECT3DDEVICE9	m_lpDirectDevice);
	// Render a surface to screen
	void RenderSurface(LPDIRECT3DDEVICE9	m_lpDirectDevice);
	// destroy this surface
	~CSurfaceDx9();
};

#endif