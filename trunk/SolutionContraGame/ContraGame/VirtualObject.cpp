#include "VirtualObject.h"


VirtualObject::VirtualObject(void)
{
}

VirtualObject::VirtualObject(D3DXVECTOR3 _position, int _width, int _height)
{
	m_Position = _position;
	m_Width = _width;
	m_Height = _height;
	m_Sprite = 0;
}

VirtualObject::~VirtualObject(void)
{
}
