#include "Rambo.h"

Rambo::Rambo()
{

}

Rambo::Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	//m_Physic = new Physic();
	//m_Physic->setPosition(_position);
	m_Position = _position;
	m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
	//m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_IDLE));
	m_RamboSprite = new RamboMoveSprite();
	//m_Physic->setPosition(D3DXVECTOR3(m_Position.x, m_Position.y, 1.0f));
	m_Position.z = 1.0f;
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
}

void Rambo::Initialize()
{

}

void Rambo::HandleInput()
{


}

void Rambo::UpdateAnimation()
{
	m_RamboSprite->UpdateAnimation();
}

void Rambo::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch(checkingObject->getTypeObject())
		{
		case ETypeObject::VIRTUAL_OBJECT:
			if(collideDirection == IDDirection::DIR_TOP)
			{
				collideDirection = IDDirection::DIR_TOP;
				//this->m_Position.x += this->m_Collision->m_MoveX;
				this->m_Position.y += this->m_Collision->m_MoveY;
				this->m_Physic->setVelocity(D3DXVECTOR2(this->m_Physic->getVelocity().x, 0));
				if(this->m_ObjectState == eObjectState::STATE_RAMBO_JUMP)
				{
					//this->m_Position.y += this->m_Collision->m_MoveY;
					this->m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
					this->m_Physic->setVelocity(D3DXVECTOR2(this->m_Physic->getVelocity().x, 0));
					TURN_ON_UPDATE_SPRITE(m_UpdateFlag);
					OutputDebugString("AAA");
				}
				break;
			}
			else if(collideDirection == IDDirection::DIR_BOTTOM)
			{
				//collideDirection = IDDirection::DIR_BOTTOM;
				break;
			}

			else if(collideDirection == IDDirection::DIR_LEFT)
			{
				//collideDirection = IDDirection::DIR_LEFT;
				break;
			}

			else if(collideDirection == IDDirection::DIR_RIGHT)
			{
				//collideDirection = IDDirection::DIR_RIGHT;
				break;
			}

			break;
		}
	}
}

void Rambo::UpdateMovement()
{
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
	this->m_Physic->UpdateMovement(&m_Position);
	CGlobal::Rambo_X = (int)(getPositionVec2().x);
	CGlobal::Rambo_Y = (int)(getPositionVec2().y);

}
void Rambo::Update()
{

}

void Rambo::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Direction == eDirection::RIGHT)
	{
		/*m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::None, m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);*/
		m_RamboSprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::None, 
			0.0f,
			1.0f,
			m_Position.z);
		return;
	}
	if (m_Direction == eDirection::LEFT)
	{
		/*m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::Horizontally,
			m_Sprite->getRotate(), m_Sprite->getScale(),
			m_Position.z);*/
		m_RamboSprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::Horizontally,
			0.0f,
			1.0f,
			m_Position.z);
		return;
	}
}

void Rambo::Release()
{

}

Rambo::~Rambo()
{

}