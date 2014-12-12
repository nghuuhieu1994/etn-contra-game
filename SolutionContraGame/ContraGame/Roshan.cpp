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
	//spriteDead = 
	m_ObjectState = eObjectState::STATE_POPUP;
	m_Sprite = spriteAlive;
}

void Roshan::UpdateAnimation()
{
	mRoshanHead->UpdateAnimation();
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

		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			isDead = true;
			m_Sprite = spriteDead;
		}
		break;
	case STATE_BOSS_DEATH:
		break;
	default:
		break;
	}
}

void Roshan::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		mRoshanHead->UpdateCollision(checkingObject);
	}
}

void Roshan::UpdateMovement()
{

}

void Roshan::Update()
{
	mRoshanHead->Update();
	
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
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 2000)
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

void Roshan::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		short colorA = 255 * mOpacity;
		if (isDead == false)
		{
			m_Sprite->Render(spriteHandle,
				getPositionVec2(),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				0.5f,
				D3DCOLOR_ARGB(colorA, 0xff, 0xff, 0xff));
		}
		else
		{
			// implement Deadstate->render
		}
	}
	if (mRoshanHead)
	{
		mRoshanHead->Render(spriteHandle);
	}
}

void Roshan::Release()
{
}
