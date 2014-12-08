#ifndef __CGAME_H__
#define __CGAME_H__

#include "CCamera.h"
#include "CGameLog.h"
#include "CGameTimeDx9.h"
#include "FrameworkDefineMacro.h"
#include "CInputDx9.h"
#include "CSpriteDx9.h"
#include "CSurfaceDx9.h"
#include "CTextureDx9.h"
#include "DemoState.h"
#include "MenuGame.h"
#include "SoundMangerDx9.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"
#include "TestSpriteState.h"
#include <d3d9.h>
#include <dsound.h>

// Factory designPattern

class CGame
{
private:
	static LRESULT CALLBACK WndProceduce(HWND hWnd, UINT  message, WPARAM wParam, LPARAM lParam);

	HWND				m_handleWindow;
	LPD3DXSPRITE		m_lpSpriteDirect3DHandle;
	LPDIRECT3D9			m_lpDirect3D;
	LPDIRECT3DDEVICE9	m_lpDirect3DDevice;
	LPDIRECTSOUND8		m_lpDirectSound;

	bool				InitializeDirect3DDevice (bool isWindowed);
	bool				InitializeDirect3DEnvironment ();
	bool				InitializeDirect3DSpriteHandle ();
	bool				InitializeDirectSound();
	bool				InitializeHandleWindow (HINSTANCE);


	float				m_fps;

	char				fps[10];
public:

	CGame();

	CGame (HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode);

	bool Initialize(HINSTANCE handleInstance, bool isWindowed);

	void Load();

	void Run();

	void Exit();

	~CGame ();
};
#endif