#include "CObjectDx9.h"

int Object::m_identifyNumber = 0;

Object::Object()
{

}

RECT Object::getBound()
{
	RECT tempBound = RECT();

	tempBound.left = m_Position.x - m_Sprite->getAnimation()->getFrameSize().x / 2;
	tempBound.right = tempBound.left + m_Sprite->getAnimation()->getFrameSize().x;
	tempBound.top = m_Position.y + m_Sprite->getAnimation()->getFrameSize().y / 2;
	tempBound.bottom = tempBound.top - m_Sprite->getAnimation()->getFrameSize().y;

	return tempBound;
}

Object::Object(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objctID)
{
	//m_Physic = new Physic();
	//m_Physic->setPosition(_position); //tach m_Physic ra khoi Object
	m_Direction = _direction;
	m_eObjectID = _objctID;
	m_TimeChangeState = 0;
	m_TimeChangeAttackDirectAttack = 0;
	++m_identifyNumber;
}

Object::~Object()
{

}