#include "CCamera.h"

Camera* Camera::s_Instance = 0;

Camera::Camera()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = SCREEN_HEIGHT;
	m_matrixTranslate._22 = -1.0f;
	m_isLockWidth = false;
	m_isLockHeight = false;
	m_isCheckFlagX = false;
	m_isCheckFlagY = false;
	m_flagStartAutoRun = D3DXVECTOR2(0, 0);
	m_flagStopAutoRun = D3DXVECTOR2(0, 0);
}

void Camera::readAutoRunScript(const char* filePath)
{
	fstream fLog(filePath, ios::in);
	fLog >> m_isCheckFlagX;
	fLog >> m_isCheckFlagY;
	fLog >> m_flagStartAutoRun.x;
	fLog >> m_flagStartAutoRun.y;
	fLog >> m_flagStopAutoRun.x;
	fLog >> m_flagStopAutoRun.y;
}

void Camera::Reset()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = SCREEN_HEIGHT;
	m_matrixTranslate._22 = -1.0f;
	m_isLockWidth = false;
	m_isLockHeight = false;
	m_isCheckFlagX = false;
	m_isCheckFlagY = false;
	m_flagStartAutoRun = D3DXVECTOR2(0, 0);
	m_flagStopAutoRun = D3DXVECTOR2(0, 0);
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
	if (m_isCheckFlagX)
	{
		if ((getBound().right - SCREEN_WIDTH/2) > m_flagStartAutoRun.x)
		{
			m_matrixTranslate._41 -= 1;
		}
		if ((getBound().right - SCREEN_WIDTH/2) >= m_flagStopAutoRun.x)
		{
			m_isCheckFlagX = false;
			m_isLockWidth = true;
		}
	}
}

D3DXMATRIX Camera::GetMatrixTranslate()
{
	return m_matrixTranslate;
}

Camera::~Camera()
{
	SAFE_DELETE(s_Instance);
}