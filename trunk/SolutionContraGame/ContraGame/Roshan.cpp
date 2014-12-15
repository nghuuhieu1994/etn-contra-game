#include "RoShan.h"

Roshan::Roshan(){}

Roshan::Roshan(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
	mOpacity = 0.0f;
}

Roshan::~Roshan()
{
}

void Roshan::Initialize()
{
	mRoshanHead = new RoshanHead(D3DXVECTOR3(m_Position.x, m_Position.y + 120, m_Position.z), eDirection::RIGHT, eObjectID::ROSHAN_HEAD);
	mRoshanHead->Initialize();
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_MAP2_BODY_ALIVE));
	spriteExploision = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_MAP2_DEATH));

	mLeftHand = new BossHand(D3DXVECTOR3(m_Position.x - 100, m_Position.y + 80, 1.0f), eDirection::LEFT, eObjectID::ROSHAN_HAND);
	mLeftHand->Initialize();
	mRightHand = new BossHand(D3DXVECTOR3(m_Position.x + 100, m_Position.y + 80, 1.0f), eDirection::RIGHT, eObjectID::ROSHAN_HAND);
	mRightHand->Initialize();

	m_ObjectState = eObjectState::STATE_POPUP;
	m_Sprite = spriteAlive;
}

void Roshan::UpdateAnimation()
{
	if (mRoshanHead)
	{
		mRoshanHead->UpdateAnimation();
	}
	if(mLeftHand)
	{
		mLeftHand->UpdateAnimation();
	}
	if(mRightHand)
	{
		mRightHand->UpdateAnimation();
	}
	switch (m_ObjectState)
	{
	case STATE_POPUP:
		//if (m_Position.y - CGlobal::Rambo_Y <= 100)
		{
			mOpacity += 0.003f;
			if (mOpacity > 1.0f)
			{
				mOpacity = 1.0f;
				m_ObjectState = STATE_ALIVE_IDLE;
			}
		}
		break;
	case STATE_ALIVE_IDLE:
		/*m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 5000)
		{
			m_TimeChangeState = 0;
			mRoshanHead->setObjectState(STATE_BEFORE_DEATH);
		}*/
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			isDead = true;
			m_Sprite = spriteDead;
		}
		spriteExploision->UpdateAnimation(250);
		break;
	case STATE_BOSS_DEATH:
		break;
	default:
		break;
	}
}

void Roshan::UpdateCollision(Object* checkingObject)
{

	if (mRightHand)
	{
		mRightHand->UpdateCollision(checkingObject);
	}
	if (mLeftHand)
	{
		mLeftHand->UpdateCollision(checkingObject);
	}
	if (!isDead)
	{
		mRoshanHead->UpdateCollision(checkingObject);
	}
}

void Roshan::UpdateMovement()
{
	if (mRightHand)
	{
		mRightHand->UpdateMovement();
	}
	if (mLeftHand)
	{
		mLeftHand->UpdateMovement();
	}
}

void Roshan::Update()
{
	if (mRoshanHead)
	{
		mRoshanHead->Update();
	}
	
	if (mLeftHand)
	{
		mLeftHand->Update();
	}
	if (mRightHand)
	{
		mRightHand->Update();
	}
	switch (m_ObjectState)
	{
	case STATE_POPUP:
		break;
	case STATE_ALIVE_IDLE:
		if (mRoshanHead->getObjectState() == STATE_BEFORE_DEATH)
		{
			m_ObjectState = STATE_BEFORE_DEATH;
		}
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::boss_dead_sfx)->Play();
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 3000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_BOSS_DEATH;
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

void Roshan::Release()
{
	if (spriteAlive)
	{
		spriteAlive->Release();
		SAFE_DELETE(spriteAlive);
		spriteExploision->Release();
		SAFE_DELETE(spriteExploision);
		mRoshanHead->Release();
		SAFE_DELETE(mRoshanHead);
	}
	/*if (mLeftHand)
	{
		mLeftHand->Release();
		SAFE_DELETE(mLeftHand);
	}
	if (mRightHand)
	{
		mRightHand->Release();
		SAFE_DELETE(mRightHand);
	}*/
}

void Roshan::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		short colorA = 255 * mOpacity;
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			0.5f,
			D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));

		if (m_ObjectState == STATE_BEFORE_DEATH)
		{
			for (int i = 0; i < 4; i++)
			{
				spriteExploision->Render(spriteHandle,
					D3DXVECTOR2(m_Position.x - 70 + i * 50, m_Position.y + 150),
					m_Sprite->getSpriteEffect(),
					m_Sprite->getRotate(),
					m_Sprite->getScale(),
					1.0f,
					D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));
				spriteExploision->Render(spriteHandle,
					D3DXVECTOR2(m_Position.x - 70 + i * 50, m_Position.y + 100),
					m_Sprite->getSpriteEffect(),
					m_Sprite->getRotate(),
					m_Sprite->getScale(),
					1.0f,
					D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));

				spriteExploision->Render(spriteHandle,
					D3DXVECTOR2(m_Position.x - 30, m_Position.y + 120 - i * 50),
					m_Sprite->getSpriteEffect(),
					m_Sprite->getRotate(),
					m_Sprite->getScale(),
					1.0f,
					D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));
				spriteExploision->Render(spriteHandle,
					D3DXVECTOR2(m_Position.x + 30, m_Position.y + 120 - i * 50),
					m_Sprite->getSpriteEffect(),
					m_Sprite->getRotate(),
					m_Sprite->getScale(),
					1.0f,
					D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));
			}
		}
	}
	if (mRoshanHead)
	{
		mRoshanHead->Render(spriteHandle);
	}
	if (mRightHand) mRightHand->Render(spriteHandle);
	if (mLeftHand) mLeftHand->Render(spriteHandle);
}

