#if !defined __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9.h>
#include <d3d9.h>
#include "CGameLog.h"
#include "FrameworkDefineMacro.h"

//#include "CGlobal.h"

class Camera
{
	static Camera*		s_Instance;
	D3DXVECTOR2	m_previousPosition;
	static bool m_isLockWidth;
	static bool m_isLockHeight;
	Camera();
	D3DXMATRIX			m_matrixTranslate;
public:
	RECT getBound();
	
	void setLockWidth(bool _isLock){ m_isLockWidth = _isLock; }
	void setLockHeight(bool _isLock){ m_isLockHeight = _isLock; }

	static Camera*		getInstance();
	void				UpdateCamera(D3DXVECTOR3* cameramanLocation);
	D3DXMATRIX			GetMatrixTranslate();
	~Camera();
};

#endif