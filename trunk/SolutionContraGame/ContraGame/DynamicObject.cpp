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
			_Velocity.x * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE),
			_Velocity.y * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE));
	
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
								m_Physic->getVelocity().x * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE),
								m_Physic->getVelocity().y * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE)
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
								m_Physic->getVelocity().x * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE),
								-300.0f * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE)
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
			  velocity.x * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE),
			  velocity.y * (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getSeconds()/((float)1/FRAME_RATE)
			);
}

DynamicObject::~DynamicObject(void)
{
}
