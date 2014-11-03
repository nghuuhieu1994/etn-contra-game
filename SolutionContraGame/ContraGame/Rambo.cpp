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
	m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
	//m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_IDLE));
	m_RamboSprite = new RamboSprite();
	//m_Physic->setPosition(D3DXVECTOR3(m_Position.x, m_Position.y, 1.0f));
	m_Position.z = 1.0f;
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
	isJump = false;
	isLieDown = false;
}

RECT Rambo::getBound()
{
	RECT tempBound = RECT();

	tempBound.left		= (long)(m_Position.x - m_RamboSprite->GetFrameSize().x / 2);
	tempBound.right		= (long)(tempBound.left + m_RamboSprite->GetFrameSize().x);
	tempBound.top		= (long)(m_Position.y + m_RamboSprite->GetFrameSize().y / 2);
	tempBound.bottom	= (long)(tempBound.top - m_RamboSprite->GetFrameSize().y);

	return tempBound;
}

void Rambo::Initialize()
{

}

void Rambo::HandleInput()
{
	if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		m_Physic->setVelocityX(2.0f);
		m_Direction = eDirection::RIGHT;
	}
	else
	{
		if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
		{
			m_Physic->setVelocityX(-2.0f);
			m_Direction = eDirection::LEFT;
		}
		else
		{
			m_Physic->setVelocityX(0.0f);
		}
	}
	//if(CInputDx9::getInstance()->IsKeyPress(DIK_SPACE) && !isJump)
	//{
	//	isJump = true;
	//	m_Physic->setVelocityY(5.0f);
	//	m_RamboSprite->SetIsJump(true);
	//}
	switch (m_ObjectState)
	{
		case STATE_RAMBO_IDLE:
			{
				if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) || CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_RUN;
					/*if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
					}
					else
					{
						if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT; 
						}
					}*/
				}
				else
				{
					if(CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
					{
						if (CInputDx9::getInstance()->IsKeyDown(DIK_UP))
						{
							break;
						}
						m_ObjectState = eObjectState::STATE_RAMBO_LIE;
						m_Position.y -= 20;
					}
					else
					{
						if (CInputDx9::getInstance()->IsKeyDown(DIK_UP))
						{
							if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
							{
								break;
							}
							m_ObjectState = eObjectState::STATE_RAMBO_AIM_UP; 
						}
						else
						{
							if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
							{
								m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
								m_Physic->setVelocityY(5.0f);
							}
						}
					}
				}
			}
			break;
		case STATE_RAMBO_JUMP:
			break;
		case STATE_RAMBO_LIE:
			{
				if(!CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
					m_Position.y += 20;
				}
				else
				{
					if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) || CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT;
						m_Position.y += 20;
					}
					else
					{
						if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
							m_Position.y += 20;
						}
					}
				}
			}
			break;
		case STATE_RAMBO_RUN:
			{
				if(!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
				}
				else
				{
					if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
					}
					else
					{
						if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT; 
						}
						else
						{
							if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
							{
								m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
								m_Physic->setVelocityY(5.0f);
							}
							else
							{
								if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
								{
									m_ObjectState = eObjectState::STATE_RAMBO_SHOOT_RUN;
								} 
							}

						}
					}
				}
			}
			break;
		case STATE_RAMBO_SHOOT:
			break;
		case STATE_RAMBO_AIM_BOTTOM_RIGHT:
			{
				if(!CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_RUN;
				}
				else
				{
					if (!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_LIE;
						m_Position.y -= 20;
					}
					else
					{
						if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
							m_Physic->setVelocityY(5.0f);
						}
					}
				}
			}
			break;
		case STATE_RAMBO_SHOOT_RUN:
			{
				if(!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
				}
				else
				{
					if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
					}
					else
					{
						if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT; 
						}
						else
						{
							if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
							{
								m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
								m_Physic->setVelocityY(5.0f);
							}
						}
					}
					if(!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_RUN;
					}
				}
			}
			break;
		case STATE_RAMBO_AIM_TOP_RIGHT:
			{
				if(!CInputDx9::getInstance()->IsKeyDown(DIK_UP))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_RUN;
				}
				else
				{
					if (!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_AIM_UP; 
					}
					else
					{
						if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
							m_Physic->setVelocityY(5.0f);
						}
					}
				}
			}
			break;
		case STATE_RAMBO_AIM_UP:
			{
				if(!CInputDx9::getInstance()->IsKeyDown(DIK_UP))
				{
					m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
				}
				else
				{
					if (CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) || CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
					{
						m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT; 
					}
					else
					{
						if(CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
						}
						else
						{
							if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
							{
								m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
								m_Physic->setVelocityY(5.0f);
							}
						}
					}
				}
			}
			break;
		case STATE_SHOOTING:
			{
				
			}
			break;
		default:
			break;
	}
	if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		m_Direction = eDirection::RIGHT;
	}
	else
	{
		if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
		{
			m_Direction = eDirection::LEFT;
		}
	}
}

void Rambo::UpdateAnimation()
{
	m_RamboSprite->UpdateAnimation(m_ObjectState);
	if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	{
		m_RamboSprite->shakeYourBodyBitch();
	}
	/*char state[100];
	sprintf(state, "%d\n", m_ObjectState);
	OutputDebugString(state);*/
}

void Rambo::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch(checkingObject->getTypeObject())
		{
		case ETypeObject::VIRTUAL_OBJECT:
			if(collideDirection == IDDirection::DIR_TOP && this->m_Physic->getVelocity().y < 0)
			{
				this->m_Position.y += this->m_Collision->m_MoveY;
				collideDirection = IDDirection::DIR_TOP;
				this->m_Physic->setVelocity(D3DXVECTOR2(this->m_Physic->getVelocity().x, 0));
				if(m_ObjectState == STATE_RAMBO_JUMP)
				{
					m_ObjectState = STATE_RAMBO_IDLE;
					this->m_Physic->setVelocity(D3DXVECTOR2(this->m_Physic->getVelocity().x, 0));
					//m_RamboSprite->SetIsJump(false);
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
	if (m_ObjectState == eObjectState::STATE_RAMBO_LIE)
	{
		m_Physic->setVelocityX(0.0f);
	}
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