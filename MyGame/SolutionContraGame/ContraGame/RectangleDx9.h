#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include <d3d9.h>
#include <d3dx9.h>

class RectangleDx9
{
private:
	// this's RECT instance to do some fucking func
	RECT	m_Rect;
	// this's Top index use in this's RECT
	//int		m_Top;
	//// this's Left index use in this's RECT
	//int		m_Left;
	//// this's Bot index use in this's RECT
	//int		m_Bot;
	//// this's Right index use in this's RECT
	//int		m_Right;
public:
	// Constructor none parameter
	RectangleDx9();
	// Constructor 4 parameter
	RectangleDx9(int top, int left, int bot, int right);
	// Constructor using 1 parameter RECT type
	RectangleDx9(const RECT &rect);
	// Constructor using 1 parameter RectangleDx9
	RectangleDx9(const RectangleDx9 &rectDx9);
	// Get this RECT for Render Function
	RECT getRECT();
	// Destroy RECT
	~RectangleDx9();
};

#endif