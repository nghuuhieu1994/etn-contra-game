#if !defined __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9.h>
#include <d3d9.h>
#include "CGameLog.h"
#include "CGlobal.h"
#include "SpriteManager.h"

class Camera
{
	static Camera*		s_Instance;
	Camera();
	D3DXMATRIX			m_matrixTranslate;
public:
	static Camera*		getInstance();
	void				UpdateCamera(D3DXVECTOR3* cameramanLocation);
	void				Render(SPRITEHANDLE spriteHandle);
	D3DXMATRIX			GetMatrixTranslate();
	~Camera();
};

#endif