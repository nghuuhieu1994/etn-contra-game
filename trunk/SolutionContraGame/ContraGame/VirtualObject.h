#include "CObjectDx9.h"
#ifndef __VIRTUAL_OBJECT_H__
#define __VIRTUAL_OBJECT_H__
class VirtualObject : public Object
{
	int m_Width;
	int m_Height;
public:
	VirtualObject(void);
	VirtualObject(D3DXVECTOR3 _position, int _width, int _height);

	~VirtualObject(void);
};

#endif