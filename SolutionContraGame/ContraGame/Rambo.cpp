#include "Rambo.h"
#define VELOCITY_Y_JUMP 4.8f
#define VELOCITY_X_MOVE_TO_RIGHT	1.1f
#define VELOCITY_Y_MOVE_TO_LEFT		-1.1f

Rambo::Rambo()
{

}

Rambo::Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position = _position;
	m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
	m_RamboSprite = new RamboSprite();
	m_Position.z = 1.0f;
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
	isJump = false;
	isFall = false;
	isLieDown = false;
	m_timeClimb = 0;
	m_timeWaterBomb = 0;
	m_timeAddBullet = 600;
	m_DirectAttack = eDirectAttack::AD_RIGHT;
	m_TypeBullet = eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO;
	m_timeDelayRunAndShootRun = 0;
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
	if(m_Physic->getAccelerate().y < -1.3f)
	{
		m_Physic->setAccelerateY(-1.3f);
	}

	if(CInputDx9::getInstance()->IsKeyDown(DIK_SPACE))
	{
		m_Position.y = 450;
	}

	switch (m_ObjectState)
	{
		case STATE_RAMBO_IDLE:
			{
				HandleInputIdleState();				
			}
			break;
		case STATE_RAMBO_JUMP:
			{
				HandleInputJumpState();
			}
			break;
		case STATE_RAMBO_LIE:
			{
				HandleInputLieState();
			}
			break;
		case STATE_RAMBO_RUN:
			{
				HandleInputRunState();
			}
			break;
		case STATE_RAMBO_SHOOT:
			break;
		case STATE_RAMBO_AIM_BOTTOM_RIGHT:
			{
				HandleInputAimBottomRightState();
			}
			break;
		case STATE_RAMBO_SHOOT_RUN:
			{
				HandleInputShootRunState();
			}
			break;
		case STATE_RAMBO_AIM_TOP_RIGHT:
			{
				HandleInputAimTopRightState();
			}
			break;
		case STATE_RAMBO_AIM_UP:
			{
				HandleInputAimUpState();
			}
			break;
		case STATE_SHOOTING:
			{
				
			}
			break;
		case STATE_RAMBO_WATER_BOMB:
			{
				HandleInputWaterBombState();
			}
			break;
		case STATE_RAMBO_DIVE:
			{
				HandleInputDiveState();
			}
			break;
		case STATE_RAMBO_SWIM:
			{
				HandleInputSwimState();
			}
			break;
		case STATE_RAMBO_CLIMB:
			{
				HandleInputClimbState();
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT:
			{
				HandleInputSwimShootState();
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT_UP:
			{
				HandleInputSwimShootUpState();
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT:
			{
				HandleInputSwimShootTopRightState();
			}
			break;
		default:
			break;
	}
	//Shoot();
	if(isFall)
	{
		m_ObjectState = eObjectState::STATE_RAMBO_FALL;
	}
	if(m_ObjectState != eObjectState::STATE_RAMBO_CLIMB)
	{
		m_timeClimb = 0;
	}
	if(m_ObjectState != eObjectState::STATE_RAMBO_WATER_BOMB)
	{
		m_timeWaterBomb = 0;
	}

	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Direction = eDirection::RIGHT;
	}
	else
	{
		if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
		{
			m_Direction = eDirection::LEFT;
		}
	}
}

int Rambo::HandleInputSwimState()
{
	m_Physic->setVelocityX(0.0f);
	if(m_Direction == eDirection::RIGHT)
	{
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}
	if(m_Direction == eDirection::LEFT)
	{
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}
	if(CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_DIVE;
	}
	if (HandleInputShooting())
	{
		if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
		{
			m_ObjectState = eObjectState::STATE_RAMBO_SWIM_SHOOT_UP;
			m_DirectAttack = eDirectAttack::AD_TOP;
			if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
			{
				m_ObjectState = eObjectState::STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT;
				if(m_Direction == eDirection::RIGHT)
				{
					m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
				}
				if(m_Direction == eDirection::LEFT)
				{
					m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
				}
			}
		}
		else
		{
			m_ObjectState = eObjectState::STATE_RAMBO_SWIM_SHOOT;
		}
		Shoot();
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		return 0;
	}
}

int Rambo::HandleInputIdleState()
{
	m_Physic->setVelocityX(0.0f);
	if (m_Direction == eDirection::LEFT)
	{
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}
	if (m_Direction == eDirection::RIGHT)
	{
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_RUN;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_LIE;
		m_Position.y -= 20;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_UP;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
		{
			m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
			if(m_Direction == eDirection::RIGHT)
			{
				m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
			}
			if(m_Direction == eDirection::LEFT)
			{
				m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
			}
		} 
	}

	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
		{
			m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT;
			if(m_Direction == eDirection::RIGHT)
			{
				m_DirectAttack = eDirectAttack::AD_BOTTOM_RIGHT;
			}
			if(m_Direction == eDirection::LEFT)
			{
				m_DirectAttack = eDirectAttack::AD_BOTTOM_LEFT;
			}
		} 
	}

	if (HandleInputShooting())
	{
		Shoot();
	}
	return 1;
}

bool Rambo::HandleInputShooting()
{
	switch (m_TypeBullet)
	{
	case DEFAULT_BULLET_OF_RAMBO:
		{
			if (CInputDx9::getInstance()->IsKeyPress(DIK_Z))
			{
				if (BulletPoolManager::getInstance()->GetAmountBulletOfType(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO) < 6)
				{
					m_RamboSprite->IncreaseTimesShake(2);
					return true;
				}
				return false;
			}
		}
		break;
	case RED_BULLET_OF_RAMBO:
		break;
	case FIRE_BULLET_OF_RAMBO:
		break;
	default:
		break;
	}
	return false;
}

int Rambo::HandleInputLieState()
{
	if(m_Direction == eDirection::RIGHT)
	{
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}
	if(m_Direction == eDirection::LEFT)
	{
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}

	if (HandleInputShooting())
	{
		Shoot();
	}

	if(!CInputDx9::getInstance()->IsKeyDown(DIK_DOWN) || CInputDx9::getInstance()->IsKeyUpDownAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
		m_Position.y += 20;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT;
		m_Position.y += 20;
		return 0;
	}
}

int Rambo::HandleInputRunState()
{
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_DirectAttack = eDirectAttack::AD_LEFT;	
	}
	if (HandleInputShooting())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SHOOT_RUN;
		Shoot();
		
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightUp() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT; 
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
	/*if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SHOOT_RUN;
		return 0;
	}*/
}

bool Rambo::isAddBullet()
{
	m_timeAddBullet += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_timeAddBullet > 500)
	{
		m_timeAddBullet = 0;
		return true;
	}
	return false;
}

int Rambo::HandleInputAimBottomRightState()
{
	
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_DirectAttack = eDirectAttack::AD_BOTTOM_RIGHT;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_DirectAttack = eDirectAttack::AD_BOTTOM_LEFT;
	}
	if (HandleInputShooting())
	{
		Shoot();
	}
	if(!CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_RUN;
		return 0;
	}	
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightUp() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_LIE;
		m_Position.y -= 20;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
}

int Rambo::HandleInputAimTopRightState()
{
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_DirectAttack = eDirectAttack::AD_TOP_LEFT;	
	}
	if (HandleInputShooting())
	{
		Shoot();
	}
	if(!CInputDx9::getInstance()->IsKeyDown(DIK_UP))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_RUN;
		return 0;
	}		
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightUp() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_UP;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
	
}

int Rambo::HandleInputAimUpState()
{
	m_DirectAttack = eDirectAttack::AD_TOP;
	if(!CInputDx9::getInstance()->IsKeyDown(DIK_UP) || CInputDx9::getInstance()->IsKeyUpDownAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
		return 0;
	}
	if (HandleInputShooting())
	{
		Shoot();	
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
}

int Rambo::HandleInputWaterBombState()
{
	m_timeWaterBomb += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_timeWaterBomb > 400)
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
	}
	return 0;
}

int Rambo::HandleInputClimbState()
{
	m_timeClimb += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_timeClimb > 400)
	{
		m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
		m_Position.y = m_Position.y + 20;
	}
	return 0;
}

int Rambo::HandleInputShootRunState()
{
	m_Physic->setVelocityX(0.0f);
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}

	if (HandleInputShooting())
	{
		Shoot();
		
	}
	if(m_RamboSprite->IsCompleteAnimation())
	{
		m_timeDelayRunAndShootRun += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timeDelayRunAndShootRun > 800)
		{
			m_ObjectState = eObjectState::STATE_RAMBO_RUN;
			m_timeDelayRunAndShootRun = 0;
		}
		return 0;
	}

	/*if(!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_RUN;
		
		return 0;
	}*/
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightUp() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_TOP_RIGHT;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_AIM_BOTTOM_RIGHT;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_X))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
}

void Rambo::Shoot()
{
	switch (m_DirectAttack)
	{
	case AD_TOP:
		{
			/*BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::FIRE_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, 2.0f), 100);
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::RED_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(1.0f, 0.0f), 1.7);
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::RED_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.5f, 0.0f), 3.7);
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::RED_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-1.0f, 0.0f), -1.7);
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::RED_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-0.5f, 0.0f), -3.7);*/
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, 2.0f), 100);
		}
		break;
	case AD_BOTTOM:
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, -2.0f), -1); 
		}
		break;
	case AD_LEFT:
		{
			/*BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::FIRE_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 0);*/
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 0);
		}
		break;
	case AD_RIGHT:
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 0);
		}
		break;
	case AD_TOP_RIGHT:
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 1);
		}
		break;
	case AD_TOP_LEFT:
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), -1);
		}
		break;
	case AD_BOTTOM_RIGHT:
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), -1);
		}
		break;
	case AD_BOTTOM_LEFT:
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 1);
		}
		break;
	default:
		break;
	}
}

D3DXVECTOR3	Rambo::GetStartPositionOfBullet()
{
	switch (m_ObjectState)
	{
		case STATE_RAMBO_IDLE:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 9, m_Position.y + 8, 0); 
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 5, m_Position.y + 8, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		case STATE_RAMBO_JUMP:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 9, m_Position.y, 0); 
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 5, m_Position.y, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		case STATE_RAMBO_LIE:
			{
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		case STATE_RAMBO_AIM_BOTTOM_RIGHT:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 24, m_Position.y - 10, 0); 
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 22, m_Position.y - 10, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y + 22, 0);
			}
			break;
		case STATE_RAMBO_SHOOT_RUN:
			{
				return D3DXVECTOR3(m_Position.x, m_Position.y + 9, 0);
			}
			break;
		case STATE_RAMBO_AIM_TOP_RIGHT:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 12, m_Position.y + 10, 0); 
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 10, m_Position.y + 10, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		case STATE_RAMBO_AIM_UP:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 9, m_Position.y + 8, 0); 
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 5, m_Position.y + 8, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT:
			{
				return D3DXVECTOR3(m_Position.x, m_Position.y - 1, 0);
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT_UP:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 9, m_Position.y + 8, 0);
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 5, m_Position.y + 8, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT:
			{
				if (m_Direction == eDirection::LEFT)
				{
					return D3DXVECTOR3(m_Position.x - 16, m_Position.y + 10, 0); 
				}
				if (m_Direction == eDirection::RIGHT)
				{
					return D3DXVECTOR3(m_Position.x + 14, m_Position.y + 10, 0);
				}
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
		default:
			{
				return D3DXVECTOR3(m_Position.x, m_Position.y, 0);
			}
			break;
	}
}

int Rambo::HandleInputJumpState()
{
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_DirectAttack = eDirectAttack::AD_RIGHT;
		if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
		{
			m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
		}
		if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
		{
			m_DirectAttack = eDirectAttack::AD_BOTTOM_RIGHT;
		}
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_DirectAttack = eDirectAttack::AD_LEFT;	
		if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
		{
			m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
		}
			if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
			{
				m_DirectAttack = eDirectAttack::AD_BOTTOM_LEFT;
			}
	}
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		m_DirectAttack = eDirectAttack::AD_TOP;
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		m_DirectAttack = eDirectAttack::AD_BOTTOM;
	}
	if (HandleInputShooting())
	{
		Shoot();
	}
	return 0;
}

int Rambo::HandleInputDiveState()
{
	if(CInputDx9::getInstance()->IsKeyUpDownAndKeyDownDown() || CInputDx9::getInstance()->IsKeyUp(DIK_DOWN))
	{
		m_ObjectState = STATE_RAMBO_SWIM;
	}
	return 1;
}

int Rambo::HandleInputSwimShootState()
{
	m_Physic->setVelocityX(0.0f);
	if(m_Direction == eDirection::RIGHT)
	{
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}
	if(m_Direction == eDirection::LEFT)
	{
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}
	//TO DO: not shooting
	
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SWIM_SHOOT_UP;
	}
	if (HandleInputShooting())
	{
		Shoot();
	}
	if(m_RamboSprite->IsCompleteAnimation())
	{
		m_timeDelayRunAndShootRun += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timeDelayRunAndShootRun > 400)
		{
			m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
			m_timeDelayRunAndShootRun = 0;
		}
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
			
		return 0;	
	}
	return 1;
}

int Rambo::HandleInputSwimShootUpState()
{
	m_DirectAttack = eDirectAttack::AD_TOP;
	if (//CInputDx9::getInstance()->IsKeyUp(DIK_Z) || //TO DO:not shooting
		CInputDx9::getInstance()->IsKeyUp(DIK_UP) || CInputDx9::getInstance()->IsKeyUpDownAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
		return 0;
	}
	if (HandleInputShooting())
	{
		if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
		{
			m_ObjectState = eObjectState::STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT;
			if(m_Direction == eDirection::RIGHT)
			{
				m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
			}
			if(m_Direction == eDirection::LEFT)
			{
				m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
			}
		}
		Shoot();
	}
	if(m_RamboSprite->IsCompleteAnimation())
	{
		m_timeDelayRunAndShootRun += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timeDelayRunAndShootRun > 800)
		{
			m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
			m_timeDelayRunAndShootRun = 0;
		}
		return 0;
	}
	return 1;
}

int Rambo::HandleInputSwimShootTopRightState()
{
	if (CInputDx9::getInstance()->IsKeyUp(DIK_UP))
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
		return 0;
	}

	if (CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightDown() ||CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightUp())
	{
		m_ObjectState = eObjectState::STATE_RAMBO_SWIM_SHOOT_UP;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
	}
	if(CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
	}
	if (HandleInputShooting())
	{
		Shoot();
	}
	if(m_RamboSprite->IsCompleteAnimation())
	{
		m_timeDelayRunAndShootRun += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timeDelayRunAndShootRun > 800)
		{
			m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
			m_timeDelayRunAndShootRun = 0;
		}
		return 0;
	}
}

void Rambo::UpdateAnimation()
{
	m_RamboSprite->UpdateAnimation(m_ObjectState);
	//THIS CODE MUST ADD IN STATE
	/*if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	{
		m_RamboSprite->shakeBody();
	}*/
	//--------------------------
	/*if (m_ObjectState != eObjectState::STATE_RAMBO_JUMP && m_ObjectState != eObjectState::STATE_RAMBO_SWIM && m_ObjectState != eObjectState::STATE_RAMBO_CLIMB && m_ObjectState != eObjectState::STATE_RAMBO_WATER_BOMB)
	{
		isFall = true; 
	}*/
	
}

void Rambo::SetFallFlag()
{
	switch (m_ObjectState)
	{
	case STATE_RAMBO_AIM_BOTTOM_RIGHT:
	case STATE_RAMBO_AIM_TOP_RIGHT:
	case STATE_RAMBO_AIM_UP:
	case STATE_RAMBO_IDLE:
	case STATE_RAMBO_LIE:
	case STATE_RAMBO_MOVE:
	case STATE_RAMBO_RUN:
	case STATE_RAMBO_SHOOT:
	case STATE_RAMBO_SHOOT_RUN:
	case STATE_RAMBO_FALL:
		isFall = true;
		break;
	case STATE_RAMBO_WATER_BOMB:
	case STATE_RAMBO_JUMP:
	case STATE_RAMBO_DIVE:
	case STATE_RAMBO_SWIM:
	case STATE_RAMBO_CLIMB:
	case STATE_RAMBO_SWIM_SHOOT:
	case STATE_RAMBO_SWIM_SHOOT_UP:
	case STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT:
		isFall = false;
		break;
	default:
		break;
	}
}

void Rambo::SetVelocityXZero()
{
	switch (m_ObjectState)
	{		
	case STATE_RAMBO_AIM_BOTTOM_RIGHT:
	case STATE_RAMBO_AIM_TOP_RIGHT:
	case STATE_RAMBO_JUMP:
	case STATE_RAMBO_MOVE:
	case STATE_RAMBO_RUN:
	case STATE_RAMBO_SHOOT:
	case STATE_RAMBO_SHOOT_RUN:
	case STATE_RAMBO_SWIM:
	case STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT:
	case STATE_RAMBO_SWIM_SHOOT:
		return;
	case STATE_RAMBO_IDLE:
	case STATE_RAMBO_SWIM_SHOOT_UP:
	case STATE_RAMBO_FALL:
	case STATE_RAMBO_CLIMB:
	case STATE_RAMBO_DIVE:
	case STATE_RAMBO_WATER_BOMB:
	case STATE_RAMBO_AIM_UP:
	case STATE_RAMBO_LIE:
		m_Physic->setVelocityX(0.0f);
		return;
	default:
		break;
	}
}

void Rambo::SetVelocityYZero()
{
	switch (m_ObjectState)
	{		
	case STATE_RAMBO_AIM_BOTTOM_RIGHT:
	case STATE_RAMBO_AIM_TOP_RIGHT:
	case STATE_RAMBO_AIM_UP:
	case STATE_RAMBO_IDLE:
	case STATE_RAMBO_JUMP:
	case STATE_RAMBO_LIE:
	case STATE_RAMBO_MOVE:
	case STATE_RAMBO_RUN:
	case STATE_RAMBO_SHOOT:
	case STATE_RAMBO_SHOOT_RUN:
	case STATE_RAMBO_FALL:
		return;
	case STATE_RAMBO_SWIM:
	case STATE_RAMBO_SWIM_SHOOT:
	case STATE_RAMBO_CLIMB:
	case STATE_RAMBO_DIVE:
	case STATE_RAMBO_WATER_BOMB:
	case STATE_RAMBO_SWIM_SHOOT_UP:
	case STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT:
		m_Physic->setVelocityY(0.0f);
		return;
	default:
		break;
	}
}

void Rambo::setRectangleCheckingObjectBelow()
{
	m_RectangleCheckingObjectBelow.left = (long)(int)(m_Position.x - 5);
	m_RectangleCheckingObjectBelow.top = (long)(int)(m_Position.y - 17);
	
	m_RectangleCheckingObjectBelow.right = (long)(int)(m_Position.x + 5);
	m_RectangleCheckingObjectBelow.bottom = (long)(int)(0);
}

int Rambo::UpdateCollisionTileBase(IDDirection collideDirection, Object* checkingObject)
{
	if(collideDirection == IDDirection::DIR_TOP && checkingObject != m_ignoreCollisionObject)
	{
		isFall = false;

		if (m_ObjectState == STATE_RAMBO_JUMP)
		{
			if (m_Physic->getVelocity().y < 0 && m_maxPositionY - checkingObject->getPositionVec2().y > 37)
			{							
				m_ObjectState = STATE_RAMBO_IDLE;
				this->m_Position.y += this->m_Collision->m_MoveY;
				m_Physic->setVelocityY(0.0f);
				m_maxPositionY = 0;
				return 0;
			}
		}
		else
		{
			if (m_ObjectState == STATE_RAMBO_FALL)
			{
				m_ObjectState = STATE_RAMBO_IDLE;
				this->m_Position.y += this->m_Collision->m_MoveY;
				m_Physic->setVelocityY(0.0f);
				return 0;
			}
			else
			{
				if(m_ObjectState == STATE_RAMBO_LIE)
				{
					this->m_Position.y += this->m_Collision->m_MoveY;
					m_Physic->setVelocityY(0.0f);
					if (CInputDx9::getInstance()->IsKeyDown(DIK_X) && m_objectBelowPrevious.size() > 1)
					{
						m_ignoreCollisionObject = checkingObject;
						m_ObjectState = STATE_RAMBO_FALL;
					}
					return 0;
				}
				else
				{
					if (m_ObjectState == eObjectState::STATE_RAMBO_SWIM || m_ObjectState == eObjectState::STATE_RAMBO_SWIM_SHOOT || 
						m_ObjectState == eObjectState::STATE_RAMBO_SWIM_SHOOT_UP || m_ObjectState == eObjectState::STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT)
					{
						if ((m_Position.x >= checkingObject->getBound().left && m_Physic->getVelocity().x > 0) ||
							(m_Position.x <= checkingObject->getBound().right && m_Physic->getVelocity().x < 0))
						{
							m_ObjectState = eObjectState::STATE_RAMBO_CLIMB;
							return 0;
						}
						return 0;
					}
					else
					{
						if(m_ObjectState == eObjectState::STATE_RAMBO_CLIMB)
						{
							m_Physic->setVelocityX(0.0f);
							return 0;
						}
						else
						{
							this->m_Position.y += this->m_Collision->m_MoveY;
							m_Physic->setVelocityY(0.0f);
							return 0;
						}
					}
				}
			}
		}
		
		
		return 0;
	}
	else if(collideDirection == IDDirection::DIR_BOTTOM)
	{
		
		if (m_ignoreCollisionObject == checkingObject)
		{
			m_ignoreCollisionObject = 0;
		}
		return 0;
	}

	else if(collideDirection == IDDirection::DIR_LEFT)
	{
		
		if (m_ObjectState == eObjectState::STATE_RAMBO_SWIM)
		{
			m_Position.x += 1;
		}
		return 0;
	}

	else if(collideDirection == IDDirection::DIR_RIGHT)
	{
		
		if (m_ObjectState == eObjectState::STATE_RAMBO_SWIM)
		{
			m_Position.x -= 1;
		}
		return 0;
	}
	return 1;
}

void Rambo::UpdateCollision(Object* checkingObject)
{
	setRectangleCheckingObjectBelow();
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
	if (checkingObject->getTypeObject() == ETypeObject::VIRTUAL_OBJECT)
	{
		if(Intersect(&checkingObject->getBound(), &m_RectangleCheckingObjectBelow))
		{
			m_objectBelowCurrent.push_back(checkingObject);
		} 
	}
	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch(checkingObject->getTypeObject())
		{
		case ETypeObject::VIRTUAL_OBJECT:
			{
				switch (checkingObject->getID())
				{
				case eObjectID::TILE_BASE:
								#pragma region TILE_BASE
					{
						UpdateCollisionTileBase(collideDirection, checkingObject);
					} 
					break;
								#pragma endregion
				case eObjectID::VIRTUAL_OBJECT_WATER:
					{
						if (collideDirection == IDDirection::DIR_TOP)
						{
							if (m_ObjectState == eObjectState::STATE_RAMBO_WATER_BOMB)
							{
								
								this->m_Position.y += this->m_Collision->m_MoveY;
							}
							else
							{
								if (m_ObjectState == eObjectState::STATE_RAMBO_JUMP || m_ObjectState == eObjectState::STATE_RAMBO_FALL)
								{
									m_ObjectState = eObjectState::STATE_RAMBO_WATER_BOMB;
									this->m_Position.y += this->m_Collision->m_MoveY - 1;
								}
								else
								{
									m_ObjectState = eObjectState::STATE_RAMBO_SWIM;
									this->m_Position.y += this->m_Collision->m_MoveY - 1;
								}
							}
						}
						isFall = false;
					}
				default:
					break;
				}
			}

		default:
			break;
		}
	}
}

void Rambo::Update(list<Object*> listObject)
{
	//START UPDATE
	//Update animation after handle input update state of Rambo
	this->UpdateAnimation();

	//set fall flag for special state for simulate gravity
	SetFallFlag();
	//set velocity to zero for dimesion X and Y for special state, if you add new state, remember to add it in 2 function
	SetVelocityXZero();
	SetVelocityYZero();

	this->UpdateMovement();

	//clear object list below Rambo for add new element in check collision sequence
	m_objectBelowCurrent.clear();
	//checking collision with object in game
	for (auto it = listObject.begin(); it != listObject.end(); ++it)
	{
		this->UpdateCollision(*it);
	}
	//clear list object of previous update and reference it to current object list
	m_objectBelowPrevious.clear();
	m_objectBelowPrevious = m_objectBelowCurrent;
	//END UPDATE
}

void Rambo::UpdateMovement()
{
	
	this->m_Physic->UpdateMovement(&m_Position);
	
	if(getBound().left < 0)
	{
		m_Position.x = 32;//hard code for sure :) getBound in different state can return different value of frame resolution and cause bug >.<
	}

	if (m_ObjectState == STATE_RAMBO_JUMP)
	{
		if (m_maxPositionY < m_Position.y)
		{
			m_maxPositionY = m_Position.y;
		}
	}
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