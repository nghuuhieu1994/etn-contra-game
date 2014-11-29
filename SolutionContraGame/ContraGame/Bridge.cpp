#include "Bridge.h"

Bridge::Bridge()
{
}

Bridge::Bridge(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void Bridge::Initialize()
{
	m_HeadTile = new BridgeTile(D3DXVECTOR3(m_Position.x - 62 / 2 - 64, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_HEAD);
	m_HeadTile->Initialize();
	RECT tempRect = m_HeadTile->getBound();
	m_TailTile = new BridgeTile(D3DXVECTOR3(m_Position.x + 64 + 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_TAIL);
	m_TailTile->Initialize();
	m_BodyTile[0] = new BridgeTile(D3DXVECTOR3(m_Position.x - 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_BODY);
	m_BodyTile[0]->Initialize();
	m_BodyTile[1] = new BridgeTile(D3DXVECTOR3(m_Position.x + 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_BODY);
	m_BodyTile[1]->Initialize();
	mListTile.push_back(m_HeadTile);
	mListTile.push_back(m_BodyTile[0]);
	mListTile.push_back(m_BodyTile[1]);
	mListTile.push_back(m_TailTile);
	m_HeadBreak = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEAD_BREAK);
	m_TailBreak = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_TAIL_BREAK);
	m_Position.z = 0.4f;
}

RECT Bridge::getBound()
{
	for(int i = 0; i < mListTile.size(); ++i)
	{
		//if(mListTile[i]->getObjectState() != eObjectState::STATE_DEATH)
		//{
			RECT tempRect;
			tempRect = mListTile[i]->getBound();
			tempRect.top -= 16;
			tempRect.left = tempRect.left;
			tempRect.bottom += 32;
			tempRect.right = tempRect.right;
			return tempRect;
		//}
		//else
		//{
			break;
		//}
	}

	if(mListTile.size() == 0)
	{
		RECT tempRect;
		tempRect.top = 0;
		tempRect.left = 0;
		tempRect.right = 0;
		tempRect.bottom = 0;

		return tempRect;
	}

	////RECT tempRect;
	////tempRect.top = 0;
	////tempRect.left = 0;
	////tempRect.bottom = 0;
	////tempRect.right = 0;

	////return tempRect;
}

void Bridge::UpdateAnimation()
{
	//m_HeadTile->UpdateAnimation();
	//m_BodyTile[0]->UpdateAnimation();
	//m_BodyTile[1]->UpdateAnimation();
	//m_TailTile->UpdateAnimation();

	for(int i = 0; i < mListTile.size(); ++i)
	{
		this->mListTile[i]->UpdateAnimation();
	}
}


void Bridge::UpdateCollision(Object* checkingObject)
{
	//m_HeadTile->UpdateCollision(checkingObject);
	//m_BodyTile[0]->UpdateCollision(checkingObject);
	//m_BodyTile[1]->UpdateCollision(checkingObject);
	//m_TailTile->UpdateCollision(checkingObject);

	for(int i = 0; i < mListTile.size(); ++i)
	{
		this->mListTile[i]->UpdateCollision(checkingObject);
	}
}

void Bridge:: UpdateMovement()
{
}

void Bridge::Update()
{
	_distanceX = m_Position.x - CGlobal::Rambo_X;
	if (_distanceX <= 100)
	{
		isDead = true;
	}
	if (isDead == true)
	{
		for(int i = 0; i < this->mListTile.size(); ++i)
		{
			if(mListTile[i]->getObjectState() == eObjectState::STATE_DEATH)
			{
				this->mListTile.erase(this->mListTile.begin());
				break;
			}
			else
			{
				this->mListTile[i]->setObjectState(eObjectState::STATE_BEFORE_DEATH);
				break;
			}
		}

		//if (m_HeadTile->isDead == false)
		//{
		//	m_HeadTile->setObjectState(STATE_BEFORE_DEATH);
		//}
		//if (m_HeadTile->getObjectState() == STATE_DEATH)
		//{
		//	this->mListTile.erase(this->mListTile.begin());
		//	if (m_BodyTile[0]->isDead != true)
		//	{
		//		m_BodyTile[0]->setObjectState(STATE_BEFORE_DEATH);
		//	}
		//}
		//else if (m_BodyTile[0]->getObjectState() == STATE_DEATH)
		//{
		//	this->mListTile.erase(this->mListTile.begin());
		//	if (m_BodyTile[1]->isDead != true)
		//	{
		//		m_BodyTile[1]->setObjectState(STATE_BEFORE_DEATH);
		//	}
		//}
		//else if (m_BodyTile[1]->getObjectState() == STATE_DEATH)
		//{
		//	this->mListTile.erase(this->mListTile.begin());
		//	if (m_TailTile->isDead != true)
		//	{
		//		m_TailTile->setObjectState(STATE_BEFORE_DEATH);
		//	}
		//}
	}

	//m_HeadTile->Update();
	//m_BodyTile[0]->Update();
	//m_BodyTile[1]->Update();
	//m_TailTile->Update();

	for(int i = 0; i < mListTile.size(); ++i)
	{
		mListTile[i]->Update();
	}

	//if(mListTile.size() == 0)
	//{
	//	this->setObjectState(eObjectState::STATE_DEATH);
	//}
}

void Bridge::Render(SPRITEHANDLE spriteHandle)
{
	m_HeadBreak->Render(spriteHandle, m_HeadTile->getPositionVec2(), ESpriteEffect::None, 0.0f, 1.0f, 1);
	m_TailBreak->Render(spriteHandle, m_TailTile->getPositionVec2() , ESpriteEffect::None, 0.0f, 1.0f, 1);
	for(int i = 0; i < mListTile.size(); ++i)
	{
		this->mListTile[i]->Render(spriteHandle);
	}
	//m_TailTile->Render(spriteHandle);
	//m_BodyTile[1]->Render(spriteHandle);
	//m_BodyTile[0]->Render(spriteHandle);
	//m_HeadTile->Render(spriteHandle);
}

void Bridge::Release()
{
}

Bridge::~Bridge()
{
}