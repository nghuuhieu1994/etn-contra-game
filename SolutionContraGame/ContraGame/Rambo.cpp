#include "Rambo.h"
#define VELOCITY_Y_JUMP 5.0f
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
	m_RamboSprite = new RamboSprite();
	//m_Physic->setPosition(D3DXVECTOR3(m_Position.x, m_Position.y, 1.0f));
	m_Position.z = 1.0f;
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
	isJump = false;
	isFall = false;
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
	if(m_Physic->getAccelerate().y < -2.0f)
	{
		m_Physic->setAccelerateY(-2.0f);
	}

	if(CInputDx9::getInstance()->IsKeyDown(DIK_SPACE))
	{
		m_Position.y = 450;
	}

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
	if (CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		m_Physic->setVelocityX(2.0f);
		m_Direction = eDirection::RIGHT;
	}
	else
	{
		if (CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
		{
			m_Physic->setVelocityX(-2.0f);
			m_Direction = eDirection::LEFT;
		}
		else
		{
			m_Physic->setVelocityX(0.0f);
			if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN) && !isJump)
			{

			}
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
								m_Physic->setVelocityY(VELOCITY_Y_JUMP);
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
								m_Physic->setVelocityY(VELOCITY_Y_JUMP);
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
							m_Physic->setVelocityY(VELOCITY_Y_JUMP);
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
								m_Physic->setVelocityY(VELOCITY_Y_JUMP);
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
							m_Physic->setVelocityY(VELOCITY_Y_JUMP);
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
								m_Physic->setVelocityY(VELOCITY_Y_JUMP);
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
	if(isFall)
	{
		m_ObjectState = eObjectState::STATE_RAMBO_FALL;
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
	if (m_ObjectState != eObjectState::STATE_RAMBO_JUMP)
	{
		isFall = true; 
	}
	/*char state[100];
	sprintf(state, "%d\n", m_ObjectState);
	OutputDebugString(state);*/
}

void Rambo::setRectangleCheckingObjectBelow()
{
	m_RectangleCheckingObjectBelow.left = (long)(int)(m_Position.x - 10);
	m_RectangleCheckingObjectBelow.top = (long)(int)(m_Position.y - 17);
	
	m_RectangleCheckingObjectBelow.right = (long)(int)(m_Position.x + 10);
	m_RectangleCheckingObjectBelow.bottom = (long)(int)(0);
}

void Rambo::UpdateCollision(Object* checkingObject)
{
	setRectangleCheckingObjectBelow();
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);//kiểm tra xem con Rambo có va chạm với đối tượng đưa vào xét hay không
	if (checkingObject->getTypeObject() == ETypeObject::VIRTUAL_OBJECT)
	{
		if(Intersect(&checkingObject->getBound(), &m_RectangleCheckingObjectBelow))
		{
			m_objectBelowCurrent.push_back(checkingObject);
		} 
	}
	if(collideDirection != IDDirection::DIR_NONE)//nếu có(tức là nó trả về hướng va chạm, va chạm tức là có hướng va chạm)
	{
		switch(checkingObject->getTypeObject())//kiểm tra xem đối tượng đó là gì
		{
		case ETypeObject::VIRTUAL_OBJECT://nếu là viên gạch
			{
				if(collideDirection == IDDirection::DIR_TOP && checkingObject != m_ignoreCollisionObject)//nếu là va chạm trên đầu của viên gạch
					// && this->m_Position.y - checkingObject->getPositionVec2().y > 35 && m_Physic->getVelocity().y < 0)
				{
					//LOGIC CỦA VA CHẠM TRÊN ĐẦU VIÊN GẠCH SẼ CODE TRONG NÀY
					//------------------------------------------------------
					this->m_Position.y += this->m_Collision->m_MoveY;
					//collideDirection = IDDirection::DIR_TOP;
					//this->m_Physic->setVelocity(D3DXVECTOR2(this->m_Physic->getVelocity().x, 0));
					m_Physic->setVelocityY(0.0f);
					if(m_ObjectState == STATE_RAMBO_JUMP)
					{
						m_ObjectState = STATE_RAMBO_IDLE;
						//this->m_Physic->setVelocity(D3DXVECTOR2(this->m_Physic->getVelocity().x, 0));
						//m_RamboSprite->SetIsJump(false);

					}
					else
					{
						if (m_ObjectState == STATE_RAMBO_FALL)
						{
							m_ObjectState = STATE_RAMBO_IDLE;
						}
						else
						{
							if(m_ObjectState == STATE_RAMBO_LIE)
							{
								if (CInputDx9::getInstance()->IsKeyDown(DIK_X) && m_objectBelowPrevious.size() > 1)
								{
									m_ignoreCollisionObject = checkingObject;
									m_ObjectState = STATE_RAMBO_FALL;
								}
							}
						}
					}
					isFall = false;
					//------------------------------------------------------
					break;
				}
				else if(collideDirection == IDDirection::DIR_BOTTOM)//nếu va chạm dưới đáy viên gạch
				{
					//collideDirection = IDDirection::DIR_BOTTOM;
					if (m_ignoreCollisionObject == checkingObject)
					{
						m_ignoreCollisionObject = 0;
					}
					break;
				}

				else if(collideDirection == IDDirection::DIR_LEFT)//nếu va chạm bên trái viên gạch
				{
					//collideDirection = IDDirection::DIR_LEFT;
					break;
				}

				else if(collideDirection == IDDirection::DIR_RIGHT)//nếu va chạm bên phải viên gạch
				{
					//collideDirection = IDDirection::DIR_RIGHT;
					break;
				}
				
				break;
			}

		default:
			break;
		}
	}
}

void Rambo::UpdateMovement()
{
	if (m_ObjectState == eObjectState::STATE_RAMBO_LIE || m_ObjectState == eObjectState::STATE_RAMBO_FALL)
	{
		m_Physic->setVelocityX(0.0f);
	}

	//this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f);
	this->m_Physic->UpdateMovement(&m_Position);
	CGlobal::Rambo_X = (int)(getPositionVec2().x);
	CGlobal::Rambo_Y = (int)(getPositionVec2().y);
	m_objectBelowCurrent.clear();
}
void Rambo::Update()
{

}

void Rambo::Render(SPRITEHANDLE spriteHandle)
{
	m_objectBelowPrevious.clear();
	m_objectBelowPrevious = m_objectBelowCurrent;
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