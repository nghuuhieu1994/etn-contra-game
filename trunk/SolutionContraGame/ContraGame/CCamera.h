#if !defined __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9.h>
#include <d3d9.h>
#include "CGameLog.h"
#include "FrameworkDefineMacro.h"
#include <fstream>

using namespace std;
//#include "CGlobal.h"

class Camera
{
	static Camera*		s_Instance;
	D3DXVECTOR2	m_previousPosition;
	bool m_isLockWidth;
	bool m_isLockHeight;
	bool m_isCheckFlagX;
	bool m_isCheckFlagY;
	D3DXVECTOR2 m_flagStartAutoRun;
	D3DXVECTOR2 m_flagStopAutoRun;
	bool m_isPause;
	bool m_tempLockHeight;
	Camera();
	D3DXMATRIX			m_matrixTranslate;
public:
	RECT getBound();
	void Reset();
	void SetTempLockHeight(bool _isLock){ m_tempLockHeight = _isLock; }
	bool GetTempLockHeight(){ return m_tempLockHeight; }
	bool IsGamePause(){ return m_isPause; }
	void setLockWidth(bool _isLock){ m_isLockWidth = _isLock; }
	void setLockHeight(bool _isLock){ m_isLockHeight = _isLock; }
	void readAutoRunScript(const char* filePath);
	static Camera*		getInstance();
	void				UpdateCamera(D3DXVECTOR3* cameramanLocation);
	D3DXMATRIX			GetMatrixTranslate();
	~Camera();
};

#endif