#ifndef __CGAME_H__
#define __CGAME_H__

#include <d3d9.h>
#include <iostream>
#include "CGlobal.h"
#include "CSpriteDx9.h"
#include "CGameTimeDx9.h"
#include "SpriteEffect.h"

using namespace std;

class CGame
{
private:
	static LRESULT CALLBACK WndProceduce(HWND hWnd, UINT  message, WPARAM wParam, LPARAM lParam);
	CGame operator=(CGame);
protected:
	//Handle of Window
	HWND				m_handleWindow;

	//Pointer of Microsoft Direct3D object
	LPDIRECT3D9			m_lpDirect3D;
	//Pointer of Device use for rendering
	LPDIRECT3DDEVICE9	m_lpDirect3DDevice;
	//Pointer of Microsft Direct3D Sprite Interface, have a bunch of method to process sprite
	LPD3DXSPRITE		m_lpSpriteDirect3DHandle;
	CGameTimeDx9*		m_GameTime;
	
	//Initialize Window Of Game
	bool				InitializeHandleWindow (HINSTANCE);

	//Initialize Direct3D Environment
	bool				InitializeDirect3DEnvironment ();
	bool				InitializeDirect3DDevice (bool isWindowed);
	bool				InitializDirect3DSpriteHandle ();
	//sprite use for testing
	CSpriteDx9*			sprite;
	// Sprite Mario Demo
	
	// fps in Game
	float					m_fps;
	// fps string
	char				fps[10];

public:
	//---------------------------------------------------
	/// @description Constructor Instance of CGame with NULL value
	/// @return new instance of CGame
	//---------------------------------------------------
	CGame();

	//---------------------------------------------------
	/// @description Constructor Instance of CGame with specified setting
	/// @param hInstance reference to Handle of Program in Main function
	/// @param scrWidth specified Width of Screen ( default is 800)
	/// @param scrHeight specified Height of Screen ( default is 600)
	/// @param frameRate specified frame rate of game ( best is 60 fps)
	/// @return new instance of CGame
	/// @warning hInstance can't be NULL
	//---------------------------------------------------
	CGame (HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode, int frameRate);
	
	//---------------------------------------------------
	/// @description Initialize CGame instance
	/// @param handleInstance reference to Handle of Program in Main function
	/// @param isWindowed use for checking game play in windowed or fullscreen
	/// @return bool for checking error
	/// @warning handleInstance can't be NULL
	//---------------------------------------------------
	bool Initialize (HINSTANCE handleInstance, bool isWindowed);
	
	//---------------------------------------------------
	/// @description Using m_lpDirect3DDevice to load texture, sound...
	/// @return void
	//---------------------------------------------------
	void Load ();

	//Run Game
	void Run ();
	
	//Exit Game
	void Exit ();

	//
	~CGame ();
};
#endif