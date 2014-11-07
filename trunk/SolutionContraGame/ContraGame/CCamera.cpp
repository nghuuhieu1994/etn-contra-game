#include "CCamera.h"

Camera* Camera::s_Instance = 0;

Camera::Camera()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = SCREEN_HEIGHT;
	m_matrixTranslate._22 = -1.0f;
}

Camera* Camera::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new Camera();
	}
	return s_Instance;
}

void Camera::UpdateCamera(D3DXVECTOR3* cameramanLocation)
{
	if (cameramanLocation->x > SCREEN_WIDTH/2)
	{
		m_matrixTranslate._41 = (float)((int)(-(cameramanLocation->x - SCREEN_WIDTH/2)));
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