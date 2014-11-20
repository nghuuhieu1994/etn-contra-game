#include "VirtualObject.h"


RECT VirtualObject::getBound()
{
	RECT tempBound = RECT();

	tempBound.left		= (long)(m_Position.x - m_Width / 2);
	tempBound.right		= (long)(tempBound.left + m_Width);
	tempBound.top		= (long)(m_Position.y + m_Height / 2);
	tempBound.bottom	= (long)(tempBound.top - m_Height);

	return tempBound;
}

VirtualObject::VirtualObject()
{

}

VirtualObject::VirtualObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : Object(_position, _direction, _objectID)

{

}

VirtualObject::VirtualObject(D3DXVECTOR3 _position, int _width, int _height, eObjectID _ObjectID) : Object(_position, eDirection::NONE, _ObjectID)
{
	m_TypeObject	=	ETypeObject::VIRTUAL_OBJECT;
	//m_Position		=	_position;
	m_Width			=	_width;
	m_Height		=	_height;
	m_Sprite		=	0;
	//m_eObjectID		=	_ObjectID;
}

void VirtualObject::Initialize()
{

}

void VirtualObject::UpdateAnimation()
{

}


void VirtualObject::UpdateCollision(Object* checkingObject)
{

}

void VirtualObject::Update()
{

}

void VirtualObject::Render(SPRITEHANDLE spriteHandle)
{

}

void VirtualObject::Release()
{
	m_Width = 0;
	m_Height = 0;
}

VirtualObject::~VirtualObject()
{

}
