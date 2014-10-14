#include "DynamicObject.h"


DynamicObject::DynamicObject(void)
{
}

DynamicObject::DynamicObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : 
Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
}

DynamicObject::~DynamicObject(void)
{
}
