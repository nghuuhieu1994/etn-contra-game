#include "Collision.h"


Collision::Collision()
{
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
}

void Collision::InitCollision()
{
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
}

IDDirection Collision::CheckCollision(DynamicObject *_DynamicObject, Object * _Object)
{
	float moveX, moveY;
	float normalX, normalY;
	float timeCollision;
	D3DXVECTOR2 velocity;
	DynamicObject *object;

	if(AABB(ConvertToBox(_DynamicObject->getBound()), ConvertToBox(_Object->getBound()), moveX, moveY) == false)
	{
		// Kiểm tra _Object có động hay không 
		if(IsMovementObject(_Object->getID()) == true)
		{
			// nếu vật có chuyển động thì ta trừ vận tốc 2 vật
			object = (DynamicObject *)_Object;	
			velocity = D3DXVECTOR2(_DynamicObject->getPhysic()->getVelocity().x - object->getPhysic()->getVelocity().x, _DynamicObject->getPhysic()->getVelocity().y - object->getPhysic()->getVelocity().y);
		}
		else
		{
			velocity = _DynamicObject->getPhysic()->getVelocity();
		}

		// nếu vật nằm trong vùng không gian của đối tượng chính
		if(AABB(_DynamicObject->GetBroadPhaseBox(velocity), ConvertToBox(_Object->getBound()), moveX, moveY) == true)
		{
			timeCollision = SweptAABB(_DynamicObject->GetBoundForDynamicObject(velocity), ConvertToBox(_Object->getBound()), normalX, normalY);

			if(timeCollision > 0.0f && timeCollision < 1.0f)
			{
				if(abs(m_MoveX) >= abs(_DynamicObject->getPhysic()->getVelocity().x * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() * timeCollision + normalX))
				{
					m_MoveX = _DynamicObject->getPhysic()->getVelocity().x * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() * timeCollision + normalX;
				}

				if(abs(m_MoveY) >= abs(_DynamicObject->getPhysic()->getVelocity().y * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() * timeCollision))
				{
					m_MoveY = _DynamicObject->getPhysic()->getVelocity().y * CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() * timeCollision;
				}

				if(normalY != 0.0f)
				{
					if(moveY != 0)
					{
						if(normalY == 1.0f)
						{
							return IDDirection::DIR_TOP;
						}
						else if(normalY == -1.0f)
						{
							return IDDirection::DIR_BOTTOM;
						}
					}
				}
				else
				{
					if(moveX != 0.0f)
					{
						if(normalX == 1.0f)
						{
							return IDDirection::DIR_RIGHT;
						}
						else if(normalX == -1.0f)
						{
							return IDDirection::DIR_LEFT;
						}
					}
				}
			}
		}
		else
		{
			//if(CheckAABB(_AnimationObject->GetBroadPhaseBox(D3DXVECTOR2(0, -300.0f)), _Object->GetBox()))
			//{
			//	return IDDirection::DIR_TOP;
			//}
		}
		
	}
	else
	{
		m_MoveY = moveY;
		m_MoveX = moveX;
		if(moveX != 0)
		{
			//if(abs(m_MoveX) < abs(moveX))
			//{
			//}
			
			if(moveX < 0.0f )
			{
				return IDDirection::DIR_LEFT;
			}
			else
			{
				return IDDirection::DIR_RIGHT;
			}
		}
		else if(moveY != 0)
		{
			//if(abs(m_MoveY) < abs(moveY))
			//{
			//}
			
			if(moveY >= 0.0f)
			{
				return IDDirection::DIR_TOP;
			}
			else
			{
				
				return IDDirection::DIR_BOTTOM;
			}
		}
		else
		{
			if((_DynamicObject->getBound().bottom == _Object->getBound().top && _DynamicObject->getBound().right == _Object->getBound().left)
				|| (_DynamicObject->getBound().bottom == _Object->getBound().top && _DynamicObject->getBound().left == _Object->getBound().right))
				return IDDirection::DIR_NONE;

			if(_DynamicObject->getBound().bottom == _Object->getBound().top)
			{
				//_AnimationObject->m_Position.y = _AnimationObject->m_Position.y - 1;
				//_DynamicObject->setPositionY(_DynamicObject->getPositionVec2().y- 0.1f);
				return IDDirection::DIR_TOP;
			}
			else if(_DynamicObject->getBound().top == _Object->getBound().bottom)
			{
				//_AnimationObject->m_Position.y = _AnimationObject->m_Position.y + 1;
				//_DynamicObject->setPositionY(_DynamicObject->getPositionVec2().y + 1);
				return IDDirection::DIR_BOTTOM;
			}
			else if(_DynamicObject->getBound().right == _Object->getBound().left)
			{
				_DynamicObject->setPositionX(_DynamicObject->getPositionVec2().x - 1);
				return IDDirection::DIR_LEFT;
			}
			else if(_DynamicObject->getBound().left == _Object->getBound().left)
			{
				_DynamicObject->setPositionX(_DynamicObject->getPositionVec2().x + 1);
				return IDDirection::DIR_RIGHT;
			}
		}
	}

	return IDDirection::DIR_NONE;
}

Collision::~Collision()
{

}
