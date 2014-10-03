#ifndef __CINPUT_H__
#define __CINPUT_H__
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameLog.h"
#include "CGlobal.h"

class CInputDx9
{
	//Manage Input of Game
	LPDIRECTINPUT8			m_lpDirectInput;
	
	LPDIRECTINPUTDEVICE8	m_lpKeyBoardDevice;
	
	LPDIRECTINPUTDEVICE8	m_lpMouseDevice;

	DIMOUSESTATE2			m_mouseState;

	DIMOUSESTATE2			m_previousMouseState;

	D3DXVECTOR2				m_cursorLocation;

	char					m_currentBuffer[256];

	char					m_previousBuffer[256];

	static CInputDx9*		s_Instance;
	CInputDx9();

public:
	static CInputDx9*		GetInstance();
	void					InitializeInput();
	void					InitializeKeyBoardDevice(HWND handleWindow);
	void					InitializeMouseDevice(HWND handleWindow);

	void					UpdateMouse();

	void					UpdateKeyBoard();

	D3DXVECTOR2				GetCursorLocation();

	bool					IsKeyDown(int keyCode);

	bool					IsKeyUp(int keyCode);

	bool					IsKeyPress(int keyCode);

	bool					IsKeyRelease(int keyCode);

	bool					IsMouseRightDown();

	bool					IsMouseLeftDown();

	bool					IsMouseRightPress();

	bool					IsMouseLeftPress();

	void					Release();
	~CInputDx9();
};

#endif