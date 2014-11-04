#include "CObjectDx9.h"

#ifndef __VIRTUAL_OBJECT_H__
#define __VIRTUAL_OBJECT_H__

class VirtualObject : public Object
{
	int m_Width;
	int m_Height;
public:
	virtual RECT getBound();
	VirtualObject(void);
	VirtualObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	VirtualObject(D3DXVECTOR3 _position, int _width, int _height, eObjectID _ObjectID);
	~VirtualObject(void);
};

#endif