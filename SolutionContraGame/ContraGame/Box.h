#ifndef __BOX_H__
#define __BOX_H__

struct BOX
{
	float x;
	float y;
	float width;
	float height;
	float vx;
	float vy;

	BOX(float _x, float _y, float _width, float _height, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		vx = _vx;
		vy = _vy;
	}

	BOX(float _x, float _y, float _width, float _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		vx = 0.0f;
		vy = 0.0f;
	}

	BOX()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
		vx = 0.0f;
		vy = 0.0f;
	}
};
#endif