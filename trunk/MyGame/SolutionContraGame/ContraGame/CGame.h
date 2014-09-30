#ifndef __CGAME_H__
#define __CGAME_H__

#include <d3d9.h>
#include <dsound.h>
#include "CGlobal.h"
#include "CSpriteDx9.h"
#include "CGameTimeDx9.h"
#include "SpriteEffect.h"
#include "SoundMangerDx9.h"
#include "SpriteManager.h"
#include "CInputDx9.h"
#include "CTextureDx9.h"
#include "CSurfaceDx9.h"
#include "Camera.h"

class CSpriteDx9;

class CGame
{
private:
	static LRESULT CALLBACK WndProceduce(HWND hWnd, UINT  message, WPARAM wParam, LPARAM lParam);
	CGame operator=(CGame);
protected:
	HWND				m_handleWindow;

	LPDIRECT3D9			m_lpDirect3D;

	LPDIRECT3DDEVICE9	m_lpDirect3DDevice;

	LPD3DXSPRITE		m_lpSpriteDirect3DHandle;

	LPDIRECTSOUND8		m_lpDirectSound;
	D3DXVECTOR3			m_UnitTest;
	CGameTimeDx9*		m_GameTime;


	bool				InitializeHandleWindow (HINSTANCE);

	bool				InitializeDirect3DEnvironment ();
	bool				InitializeDirect3DDevice (bool isWindowed);
	bool				InitializeDirect3DSpriteHandle ();

	bool				InitializeDirectSound();

	CSpriteDx9* texture;
	float		angle;

	float					m_fps;

	char				fps[10];
	eSpriteEffect		m_testSpriteEffect;
public:

	CGame();

	CGame (HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode);
	
	bool Initialize (HINSTANCE handleInstance, bool isWindowed);
	
	void Load ();

	void Run ();
	
	void Exit ();

	//
	~CGame ();
};
#endif