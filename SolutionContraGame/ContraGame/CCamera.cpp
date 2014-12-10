#include "CCamera.h"

Camera* Camera::s_Instance = 0;
bool	Camera::m_isLockWidth = false;
bool	Camera::m_isLockHeight = false;


Camera::Camera()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = SCREEN_HEIGHT;
	m_matrixTranslate._22 = -1.0f;
}

void Camera::Reset()
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

RECT Camera::getBound()
{
	RECT tempRect = RECT();

	tempRect.top = (long)(m_matrixTranslate._42);
	tempRect.left = (long)(-m_matrixTranslate._41);
	tempRect.right = (long)(tempRect.left + SCREEN_WIDTH);
	tempRect.bottom = (long)(tempRect.top - SCREEN_HEIGHT);

	return tempRect;
}

void Camera::UpdateCamera(D3DXVECTOR3* cameramanLocation)
{
	if (cameramanLocation->x > SCREEN_WIDTH/2 && !m_isLockWidth)
	{
		if (m_previousPosition.x > (float)((int)(-(cameramanLocation->x - SCREEN_WIDTH/2))))
		{
			m_matrixTranslate._41 = (float)((int)(-(cameramanLocation->x - SCREEN_WIDTH/2))); 
		}
	}

	
	if (cameramanLocation->y > SCREEN_HEIGHT/2 && !m_isLockHeight)
	{
		if (m_previousPosition.y < (float)(SCREEN_HEIGHT + (int)((cameramanLocation->y - SCREEN_HEIGHT/2))))
		{
			m_matrixTranslate._42 = (float)(SCREEN_HEIGHT + (int)((cameramanLocation->y - SCREEN_HEIGHT/2))); 
		}
	}
	this->m_previousPosition.x = m_matrixTranslate._41;
	this->m_previousPosition.y = m_matrixTranslate._42;
}

D3DXMATRIX Camera::GetMatrixTranslate()
{
	return m_matrixTranslate;
}

Camera::~Camera()
{
	SAFE_DELETE(s_Instance);
}