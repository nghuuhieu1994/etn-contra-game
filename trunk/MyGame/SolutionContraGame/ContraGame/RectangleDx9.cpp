#include "RectangleDx9.h"

RectangleDx9::RectangleDx9()
{
	this->m_Rect.bottom = 0;
	this->m_Rect.top = 0;
	this->m_Rect.left = 0;
	this->m_Rect.right = 0;
}

RectangleDx9::RectangleDx9(int top, int left, int bot, int right)
{
	this->m_Rect.bottom			= bot;
	this->m_Rect.top			= top;
	this->m_Rect.left			= left;
	this->m_Rect.right			= right;
}
RectangleDx9::RectangleDx9(const RECT &rect)
{
	RectangleDx9(rect.top, rect.left, rect.bottom, rect.right);
}
RectangleDx9::RectangleDx9(const RectangleDx9 &rectDx9)
{
	RectangleDx9(rectDx9.m_Rect.top, rectDx9.m_Rect.left, rectDx9.m_Rect.bottom, rectDx9.m_Rect.right); 
}
RECT RectangleDx9::getRECT()
{
	return m_Rect;
}

RectangleDx9::~RectangleDx9()
{

}