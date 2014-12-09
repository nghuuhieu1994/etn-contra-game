#include "CapsuleBoss.h"

#define VELOC_X_CAPSULE_BOSS 2
#define VELOC_Y_CAPSULE_BOSS -2
#define ACEL_Y_CAPSULE_BOSS -0.03f
#define TIME_CAPSULE_BOSS_FALL 1500

CapsuleBoss::CapsuleBoss(){
}
CapsuleBoss::CapsuleBoss(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID){
	isFall = false;
	isChangeDirect = false;
	switch (_direction)
	{
	case eDirection::RIGHT:
		m_Physic->setVelocityX(VELOC_X_CAPSULE_BOSS);
		m_Physic->setVelocityY(0);
		break;
	case eDirection::LEFT:
		m_Physic->setVelocityX(-VELOC_X_CAPSULE_BOSS);
		m_Physic->setVelocityY(0);
		break;
	default:
		break;
	}
}

void CapsuleBoss::Initialize()
{
	m_AttackCounter = 1;
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_CAPSULE_BOSS));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Position.z = 1.0f;
	m_Sprite = spriteAlive;
}

void CapsuleBoss::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Sprite->UpdateAnimation(120);
		break;
	case STATE_BEFORE_DEATH:
		if (!isDead)
		{
			isDead = true;
			m_Sprite = spriteDead;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void CapsuleBoss::UpdateCollision(Object* checkingObject)
{
	if (isDead == false)
	{
		if (checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
#pragma region BulletCollision
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection != IDDirection::DIR_NONE)
			{
				Bullet* tempBullet = (Bullet*) (checkingObject);
				if (tempBullet->getTypeBullet() == eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO)
				{
					if (m_AttackCounter > 0)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						--m_AttackCounter;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::RED_BULLET_OF_RAMBO)
				{
					checkingObject->setObjectState(eObjectState::STATE_DEATH);
					if (m_AttackCounter >= 2)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 2;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::FIRE_BULLET_OF_RAMBO)
				{
					if (m_AttackCounter >= 4)
					{
						m_AttackCounter -= 4;
					}
				}

				if (m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
#pragma endregion BulletCollision
		}
		if (checkingObject->getID() == eObjectID::TILE_BASE)
		{
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection == IDDirection::DIR_BOTTOM)
			{
				if (isChangeDirect == false)
				{
					isChangeDirect = true;
					float VeclocX = m_Physic->getVelocity().x;
					m_Physic->setVelocityX(-VeclocX);
					m_Physic->setAccelerateY(0);
					m_Physic->setVelocityY(0);
				}
			}
		}
	}
}
void CapsuleBoss::UpdateMovement()
{
	if (isFall == false)
	{
		this->m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeDirectAttack > TIME_CAPSULE_BOSS_FALL)
		{
			m_TimeChangeDirectAttack = 0;
			isFall = true;
			//float VeclocX = m_Physic->getVelocity().x;
			m_Physic->setVelocityX(0);
			m_Physic->setVelocityY(VELOC_Y_CAPSULE_BOSS);
			m_Physic->setAccelerateY(ACEL_Y_CAPSULE_BOSS);
		}
	}
	m_Physic->UpdateMovement(&m_Position);
}
void CapsuleBoss::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1000)
			{
				m_ObjectState = eObjectState::STATE_DEATH;
				m_TimeChangeState = 0;
			}
		}
		break;
	case STATE_DEATH:
		Release();
		break;
	default:
		break;
	}
}

void CapsuleBoss::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);
	}
}

void CapsuleBoss::Release()
{
	m_Sprite = 0;
	spriteAlive->Release();
	SAFE_DELETE(spriteAlive);
	spriteDead->Release();
	SAFE_DELETE(spriteDead);
}

CapsuleBoss::~CapsuleBoss(){

}