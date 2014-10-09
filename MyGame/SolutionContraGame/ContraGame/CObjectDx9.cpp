#include "CObjectDx9.h"

Object::Object()
{

}

Object::Object(D3DXVECTOR3 _position, eDirection _direction)
{
	m_Direction = _direction;
	m_Physic = new Physic();
	m_Physic->setPosition(_position);
}

Object::~Object()
{

}