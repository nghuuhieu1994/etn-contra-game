#include "RoshanHead.h"

#ifndef TIME_HEADBOSS_UPDATE_ANIMATION
#define TIME_HEADBOSS_UPDATE_ANIMATION 500
#endif
RoshanHead::RoshanHead(){}

RoshanHead::RoshanHead(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
	isShoot = false;
	mOpacity = 0.0f;
}
RoshanHead::~RoshanHead(){}

void RoshanHead::Shoot()
{
	mListRoshanBullet.push_back(new BossBullet(m_Position, m_Direction, eObjectID::BULLET_ENEMY));
	mListRoshanBullet.back()->Initialize();
	mListRoshanBullet.back()->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));

	mListRoshanBullet.push_back(new BossBullet(m_Position, m_Direction, eObjectID::BULLET_ENEMY));
	mListRoshanBullet.back()->Initialize();
	mListRoshanBullet.back()->getPhysic()->setVelocity(D3DXVECTOR2(0.5f, 0));

	mListRoshanBullet.push_back(new BossBullet(m_Position, m_Direction, eObjectID::BULLET_ENEMY));
	mListRoshanBullet.back()->Initialize();
	mListRoshanBullet.back()->getPhysic()->setVelocity(D3DXVECTOR2(-0.5f, 0));
}

void RoshanHead::Initialize()
{
	m_AttackCounter = 100;
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_HEAD));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	//m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_ObjectState = eObjectState::STATE_POPUP;
	m_Sprite = spriteAlive;
	m_Position.z = 1.0f;
}

void RoshanHead::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_POPUP:
		//if (m_Position.y - CGlobal::Rambo_Y <= 250)
		{
			mOpacity += 0.003f;
			if (mOpacity > 1.0f)
			{
				mOpacity = 1.0f;
				m_Sprite->getAnimationAction()->setIndexStart(0);
				m_Sprite->getAnimationAction()->setIndexEnd(2);
				m_ObjectState = STATE_ALIVE_IDLE;
			}
		}
		break;
	case STATE_ALIVE_IDLE:
		m_Sprite->UpdateAnimation(TIME_HEADBOSS_UPDATE_ANIMATION);
		break;
	case STATE_SHOOTING:
		m_Sprite->UpdateAnimation(TIME_HEADBOSS_UPDATE_ANIMATION);
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
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
void RoshanHead::UpdateCollision(Object* checkingObject)
{
	if (mListRoshanBullet.empty() != true)
	{
		for (list<BossBullet*>::iterator i = mListRoshanBullet.begin(); i != mListRoshanBullet.end(); i++)
		{
			(*i)->UpdateAnimation();
			(*i)->UpdateMovement();
			(*i)->Update();
			(*i)->UpdateCollision(checkingObject);
		}
	}

	if (isDead == false)
	{

		if (mListRoshanBullet.empty() != true)
		{
			for (list<BossBullet*>::iterator i = mListRoshanBullet.begin(); i != mListRoshanBullet.end(); i++)
			{
				(*i)->UpdateAnimation();
				(*i)->UpdateMovement();
				(*i)->Update();
				(*i)->UpdateCollision(checkingObject);				
			}
		}

		if (checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
			if (abs(checkingObject->getPositionVec2().x - m_Position.x) < 30)
			{
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
			}
		}
	}
}
void RoshanHead::UpdateMovement()
{
}
void RoshanHead::Update()
{
	if (mListRoshanBullet.empty() != true)
	{
		for (list<BossBullet*>::iterator i = mListRoshanBullet.begin(); i != mListRoshanBullet.end(); )
		{
			if ((*i)->getObjectState() == STATE_DEATH)
			{
				(*i)->Release();
				SAFE_DELETE(*i);
				i = mListRoshanBullet.erase(i);
				//mListRoshanBullet.remove( (BossBullet*)*i );
				//mListRoshanBullet.
			}
			else
			{
				i++;
			}
		}
	}
	switch (m_ObjectState)
	{
	case STATE_POPUP:
		break;
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > TIME_HEADBOSS_UPDATE_ANIMATION * 12)
		{
			m_TimeChangeState = 0;
			m_Sprite->getAnimationAction()->setIndexStart(3);
			m_Sprite->getAnimationAction()->setIndexEnd(8);
			isShoot = true;
			m_ObjectState = STATE_SHOOTING;
		}
		break;
	case STATE_SHOOTING:
		if (isShoot)
		{
			m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeDirectAttack > TIME_HEADBOSS_UPDATE_ANIMATION * 4)
			{
				m_TimeChangeDirectAttack = 0;
				Shoot();
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::bullet_L_sfx)->Play();
				isShoot = false;
			}
		}
		else
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > TIME_HEADBOSS_UPDATE_ANIMATION * 2)
			{
				m_TimeChangeState = 0;
				m_Sprite->getAnimationAction()->setIndexStart(0);
				m_Sprite->getAnimationAction()->setIndexEnd(2);
				m_ObjectState = STATE_ALIVE_IDLE;
			}
		}
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1500)
			{
				m_TimeChangeState = 0;
				m_ObjectState = STATE_DEATH;
			}
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}

void RoshanHead::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != 0)
	{
		short colorA = 255 * mOpacity;
		if (isDead == false)
		{
			m_Sprite->Render(spriteHandle,
				getPositionVec2(),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z,
				D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));
		}
		else
		{
			// implement Deadstate->render
		}
	}
	if (mListRoshanBullet.empty() != true)
	{
		for (list<BossBullet*>::iterator i = mListRoshanBullet.begin(); i != mListRoshanBullet.end(); i++)
		{
			(*i)->Render(spriteHandle);
		}
	}
}

void RoshanHead::Release()
{
	m_Sprite = 0;
	spriteAlive->Release();
	SAFE_DELETE(spriteAlive);
	spriteDead->Release();
	SAFE_DELETE(spriteDead);
	if (mListRoshanBullet.empty() != true)
	{
		for (list<BossBullet*>::iterator i = mListRoshanBullet.begin(); i != mListRoshanBullet.end(); i++)
		{
			(*i)->Release();
			SAFE_DELETE(*i);
			mListRoshanBullet.clear();
		}
	}
}