#include "BigCapsuleBoss.h"
#ifndef BOSS_ANIMATION_TIME
#define BOSS_ANIMATION_TIME 800
#endif

BigCapsuleBoss::BigCapsuleBoss(){

}

BigCapsuleBoss::BigCapsuleBoss(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
	isShoot = false;
	mOpacity = 1.0f;

	listPosition[0] = _position;
	listPosition[1].x = _position.x - 50;
	listPosition[1].y = _position.y + 50;
	listPosition[1].z = _position.z;
	listPosition[2].x = _position.x - 50;
	listPosition[2].y = _position.y - 50;
	listPosition[2].z = _position.z;
	listPosition[3].x = _position.x + 50;
	listPosition[3].y = _position.y + 50;
	listPosition[3].z = _position.z;
	listPosition[4].x = _position.x + 50;
	listPosition[4].y = _position.y - 50;
	listPosition[4].z = _position.z;
}

BigCapsuleBoss::~BigCapsuleBoss(){}

void BigCapsuleBoss::Shoot()
{
	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::bullet_S_sfx)->Play();

	m_ListBullet.push_back(new BossBullet(getPositionVec3(), m_Direction, eObjectID::BULLET_ENEMY));
	m_ListBullet.back()->Initialize();
	m_ListBullet.back()->getPhysic()->setVelocity(D3DXVECTOR2(0, -1.5f));

	if (m_Direction == eDirection::RIGHT)
	{
		m_ListEnemy.push_back(new CapsuleBoss( D3DXVECTOR3(m_Position.x, m_Position.y + 20, m_Position.z - 0.5f), m_Direction, eObjectID::CAPSULE_BOSS));
		m_ListEnemy.back()->Initialize();
		m_Direction = eDirection::LEFT;
	}
	else
	{
		m_ListEnemy.push_back(new CapsuleBoss( D3DXVECTOR3(m_Position.x, m_Position.y + 20, m_Position.z - 0.5f), m_Direction, eObjectID::CAPSULE_BOSS));
		m_ListEnemy.back()->Initialize();
		m_Direction = eDirection::RIGHT;
	}
}

void BigCapsuleBoss::Initialize()
{
	m_AttackCounter = 50;
	BulletCounter = 0;
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BIG_CAPSULE_BOSS));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));

	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
	m_Sprite = spriteAlive;
}

void BigCapsuleBoss::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		mOpacity = 1.0f;
		m_Sprite->UpdateAnimation(BOSS_ANIMATION_TIME);
		break;
	case STATE_SHOOTING:
		m_Sprite->getAnimationAction()->setIndexStart(7);
		m_Sprite->getAnimationAction()->setIndexEnd(11);
		m_Sprite->UpdateAnimation(BOSS_ANIMATION_TIME);
		break;
	case STATE_BEFORE_DEATH: // thật ra cái này là invi chứ không có chết đâu nha >:(
		if (mOpacity > 0.0f)
		{
			mOpacity -= 0.005f;
		}
		else
		{
			mOpacity = 0.0f;
		}
		m_Sprite->getAnimationAction()->setCurrentFrame(11);
		break;
	case STATE_EXPLOISION:
		if (isDead == false)
		{
			// gan' spritedead
			m_Sprite = spriteDead;
			isDead = true;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_BOSS_DEATH:
		break;
	default:
		break;
	}
}

void BigCapsuleBoss::UpdateCollision(Object* checkingObject)
{
	if (isDead == false)
	{
#pragma region UpdateListEnemy
		if (m_ListEnemy.empty() == false)
		{
			for (list<CapsuleBoss*>::iterator i = m_ListEnemy.begin(); i != m_ListEnemy.end(); i++)
			{
				(*i)->UpdateCollision(checkingObject); // Ham nay tam tho`i tat' di.
			}
		}
		if (m_ListBullet.empty() != true)
		{
			for (list<BossBullet*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end(); i++)
			{
				(*i)->UpdateCollision(checkingObject); 
			}
		}
#pragma endregion UpdateListEnemy
		
		if (checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
#pragma region BulletCollision
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection != IDDirection::DIR_NONE && m_ObjectState == STATE_SHOOTING)
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
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 4;
					}
				}

				if (m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_EXPLOISION;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::boss_dead_sfx)->Play();
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
#pragma endregion BulletCollision
		}
		// when AttackCounter == 0; ObjectState = STATE_EXPLOISION;
	}
}

void BigCapsuleBoss::UpdateMovement()
{
}

void BigCapsuleBoss::Update()
{
	if(m_Position.x - CGlobal::Rambo_X < 397)
	{
	if (m_ListEnemy.empty() == false)
	{
		for (list<CapsuleBoss*>::iterator i = m_ListEnemy.begin(); i != m_ListEnemy.end(); )
		{

				(*i)->Update();
				(*i)->UpdateAnimation();
				(*i)->UpdateMovement();


			if ((*i)->getObjectState() == STATE_DEATH)
			{
				(*i)->Release();
				SAFE_DELETE(*i);
				i = m_ListEnemy.erase(i);
			}
			else
			{
				i++;
			}
		}
	}

	if (m_ListBullet.empty() == false)
	{
		for (list<BossBullet*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end();)
		{

			(*i)->Update();
			(*i)->UpdateAnimation();
			(*i)->UpdateMovement();


			if ((*i)->getObjectState() == STATE_DEATH)
			{
				(*i)->Release();
				SAFE_DELETE(*i);
				i = m_ListBullet.erase(i);
			}
			else
			{
				i++;
			}
		}
	}

	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 4000)
		{
			m_TimeChangeState = 0;
			m_ObjectState = STATE_SHOOTING;
		}
		break;
	case STATE_SHOOTING:
		m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeDirectAttack > 800)
		{
			m_TimeChangeDirectAttack = 0;
			BulletCounter += 1;
			Shoot();

			if (BulletCounter == 8)
			{
				BulletCounter = 0;				
				m_ObjectState = STATE_BEFORE_DEATH; // that ra cai nay a invi chu khong co chet.
			}
		}
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 12000)
		{
			m_TimeChangeState = 0;
			int n = rand() % 5;
			m_Position = listPosition[n];
			m_Sprite->getAnimationAction()->setCurrentFrame(0);
			m_Sprite->getAnimationAction()->setIndexStart(0);
			m_Sprite->getAnimationAction()->setIndexEnd(11);
			m_ObjectState = STATE_ALIVE_IDLE;
		}
		break;
	case STATE_EXPLOISION:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1500)
			{
				m_TimeChangeState = 0;
				m_ObjectState = STATE_BOSS_DEATH;
				this->isDead = true;
			}
		}
		break;
	case STATE_BOSS_DEATH:
		Release();
		break;
	default:
		break;
	}
	}
}

void BigCapsuleBoss::Render(SPRITEHANDLE spriteHandle)
{
	if (m_ListEnemy.empty() != true)
	{
		for (list<CapsuleBoss*>::iterator i = m_ListEnemy.begin(); i != m_ListEnemy.end(); i++)
		{
			(*i)->Render(spriteHandle);
		}
	}
	if (m_ListBullet.empty() != true)
	{
		for (list<BossBullet*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end(); i++)
		{
			(*i)->Render(spriteHandle);
		}
	}
	if (m_Sprite != 0)
	{
		short colorA = (short)(255 * mOpacity);
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z,
			D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));
	}

}

void BigCapsuleBoss::Release()
{
	if (m_ListEnemy.empty() == false)
	{
		for (list<CapsuleBoss*>::iterator i = m_ListEnemy.begin(); i != m_ListEnemy.end();)
		{
			(*i)->Release();
			SAFE_DELETE((*i));
			i = m_ListEnemy.erase(i);
		}
	}
	if (m_ListBullet.empty() != true)
	{
		for (list<BossBullet*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end(); i++)
		{
			(*i)->Release();
			SAFE_DELETE(*i);
			i = m_ListBullet.erase(i);
		}
	}
	m_Sprite = 0;
	if (spriteAlive)
	{
		spriteAlive->Release();
		SAFE_DELETE(spriteAlive);
	}
	if (spriteDead)
	{
		spriteDead->Release();
		SAFE_DELETE(spriteDead);
	}
	// release 1 sprite alive and dead. we're w8ing for Right's SpriteDead
}