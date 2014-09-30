#include "CCamera.h"

Camera* Camera::s_Instance = 0;

Camera::Camera()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = 600;
	m_matrixTranslate._22 = -1.0f;
}

Camera* Camera::GetInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new Camera();
	}
	return s_Instance;
}

void Camera::UpdateCamera(D3DXVECTOR3* cameramanLocation)
{
	if (cameramanLocation->x > WIDTH/2)
	{
		m_matrixTranslate._41 = -(cameramanLocation->x - WIDTH/2);
	}
	else
		m_matrixTranslate._41 = 0;
	
}

D3DXMATRIX Camera::GetMatrixTranslate()
{
	return m_matrixTranslate;
}

Camera::~Camera()
{
	SAFE_DELETE(s_Instance);
}