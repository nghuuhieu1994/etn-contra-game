#ifndef _CAMERA_H_
#define _CAMERA_H_
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#include <d3dx9.h>

class Camera
{
public:
	float _X, _Y, _lastY, _hY;

	D3DXMATRIX _matrix;
	RECT _rect;
public:
	Camera();
	void Update(D3DXVECTOR2 character);
};

#endif