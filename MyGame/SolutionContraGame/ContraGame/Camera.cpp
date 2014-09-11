#include "Camera.h"


Camera::Camera()
{
	D3DXMatrixIdentity(&_matrix);
	_matrix._22 = -1;
	_Y = _lastY = 600;
	//_hY = _Y / 2;
}

void Camera::Update(D3DXVECTOR2 character)
{
	_X = character.x - SCREEN_WIDTH / 2;

	if (_X < 0)
	{
		_X = 0;
	}

	if (_Y < 600)
	{
		_Y = 600;
	}
	else if (character.y > _Y - 150)
	{
		_Y += 2;
	}
	else if (character.y < _Y - 450)
	{
		_Y -= 3;
	}
	

	_matrix._41 = -(_X);
	_matrix._42 = _Y;

	_rect.left = _X;
	_rect.right = _rect.left + SCREEN_WIDTH;
	_rect.top = _Y;
	_rect.bottom = _rect.top - SCREEN_HEIGHT;
}