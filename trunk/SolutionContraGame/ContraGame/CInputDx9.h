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
	bool					m_PressKey[256];
	char					m_currentBuffer[256];
	char					m_previousBuffer[256];
	CInputDx9();
	D3DXVECTOR2				m_cursorLocation;
	DIDEVICEOBJECTDATA		m_KeyEvents[1024];
	DIMOUSESTATE2			m_mouseState;
	DIMOUSESTATE2			m_previousMouseState;
	LPDIRECTINPUT8			m_lpDirectInput;
	LPDIRECTINPUTDEVICE8	m_lpKeyBoardDevice;
	LPDIRECTINPUTDEVICE8	m_lpMouseDevice;
	static CInputDx9*		s_Instance;
public:
	bool					IsKeyDown(int keyCode);
	bool					IsKeyPress(int keyCode);
	bool					IsKeyRelease(int keyCode);
	bool					IsKeyUp(int keyCode);
	
	bool					IsKeyLeftDownAndKeyRightDown();
	bool					IsKeyLeftDownAndKeyRightUp();
	bool					IsKeyLeftUpAndKeyRightDown();
	bool					IsKeyLeftUpAndKeyRightUp();
	bool					IsMouseLeftDown();
	bool					IsMouseLeftPress();
	bool					IsMouseRightDown();
	bool					IsMouseRightPress();
	bool					IsKeyUpUpAndKeyDownUp();
	bool					IsKeyUpDownAndKeyDownDown();
	bool					IsKeyUpDownAndKeyDownUp();
	bool					IsKeyUpUpAndKeyDownDown();

	D3DXVECTOR2				GetCursorLocation();
	static CInputDx9*		getInstance();
	void					InitializeInput();
	void					InitializeKeyBoardDevice(HWND handleWindow);
	void					InitializeMouseDevice(HWND handleWindow);
	void					Release();
	void					UpdateKeyBoard();
	void					UpdateMouse();
	~CInputDx9();
};

#endif