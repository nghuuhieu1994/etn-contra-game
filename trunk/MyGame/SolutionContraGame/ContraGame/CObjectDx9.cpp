#include "CObjectDx9.h"

Object::Object()
{

}

Object::Object(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objctID)
{
	m_Direction = _direction;
	m_eObjectID = _objctID;
	m_Physic = new Physic();
	m_Physic->setPosition(_position);
}

Object::~Object()
{

}