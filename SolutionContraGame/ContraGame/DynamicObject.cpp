#include "DynamicObject.h"


DynamicObject::DynamicObject(void)
{
}

DynamicObject::DynamicObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : 
Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
	m_Position = _position;
	m_DirectAttack = eDirectAttack::NONE;
	this->m_Collision = new Collision();
}

void DynamicObject::UpdateBound()
{
	Object::getBound();
}

// tạo một broadphase với đối tượng thứ 2 là di chuyển
BOX DynamicObject::GetBroadPhaseBox(D3DXVECTOR2 _Velocity)
{
	BOX box(
			ConvertToBox(getBound()).x, 
			ConvertToBox(getBound()).y,
			ConvertToBox(getBound()).width, 
			ConvertToBox(getBound()).height, 
			_Velocity.x * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds(),
			_Velocity.y * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds());
	
	return ConvertToBroadPhase(box);
}

// tạo một broadphase với đối tượng thứ 2 là tĩnh
BOX DynamicObject::GetBroadPhaseBox()
{
	if(m_Physic->getVelocity().y != 0)
	{
		return ConvertToBroadPhase(
							BOX(
								ConvertToBox(getBound()).x,
								ConvertToBox(getBound()).y,
								ConvertToBox(getBound()).width,
								ConvertToBox(getBound()).height,
								m_Physic->getVelocity().x * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds(),
								m_Physic->getVelocity().y * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds()
								)
			);
	}
	else // Lúc này gia tốc bằng 0, tăng tốc độ theo chiều âm để đảm bảo vật luôn va chạm top
	{
		return ConvertToBroadPhase(
							BOX(
								ConvertToBox(getBound()).x,
								ConvertToBox(getBound()).y,
								ConvertToBox(getBound()).width,
								ConvertToBox(getBound()).height,
								m_Physic->getVelocity().x * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds(),
								-300.0f * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds()
								)
			);
	}
}

BOX DynamicObject::GetBoundForDynamicObject(D3DXVECTOR2 velocity)
{
	return BOX(
			  ConvertToBox(getBound()).x,
			  ConvertToBox(getBound()).y,
			  ConvertToBox(getBound()).width,
			  ConvertToBox(getBound()).height,
			  m_Physic->getVelocity().x * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds(),
			  m_Physic->getVelocity().x  * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds()
			);
}

DynamicObject::~DynamicObject(void)
{
}
