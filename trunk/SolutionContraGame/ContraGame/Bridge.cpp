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
	m_HeadTile = new BridgeTile(D3DXVECTOR3(m_Position.x - 62 / 2 - 65, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_HEAD);
	m_HeadTile->Initialize();
	RECT tempRect = m_HeadTile->getBound();
	m_TailTile = new BridgeTile(D3DXVECTOR3(m_Position.x + 65 + 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_TAIL);
	m_TailTile->Initialize();
	m_BodyTile[0] = new BridgeTile(D3DXVECTOR3(m_Position.x - 62 / 2 - 1, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_BODY);
	m_BodyTile[0]->Initialize();
	m_BodyTile[1] = new BridgeTile(D3DXVECTOR3(m_Position.x + 62 / 2 + 1, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_BODY);
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
	/*for(int i = 0; i < mListTile.size(); ++i)
	{
			RECT tempRect;
			tempRect = mListTile[i]->getBound();
			tempRect.top -= 16;
			tempRect.left = tempRect.left;
			tempRect.bottom += 32;
			tempRect.right = tempRect.right;
			return tempRect;
	}*/
	
	if((int)mListTile.size() == 0)
	{
		RECT tempRect;
		tempRect.top = 0;
		tempRect.left = 0;
		tempRect.right = 0;
		tempRect.bottom = 0;

		return tempRect;
	}
	else
	{
		RECT rt;
		rt.top = (int)mListTile[0]->getBound().top - 16;
		rt.bottom = mListTile[mListTile.size() - 1]->getBound().bottom;
		rt.left = mListTile[0]->getBound().left;
		rt.right = mListTile[mListTile.size() - 1]->getBound().right;
		
		return rt;
	}


}

void Bridge::UpdateAnimation()
{
	for(int i = 0; i < mListTile.size(); ++i)
	{
		this->mListTile[i]->UpdateAnimation();
	}
}


void Bridge::UpdateCollision(Object* checkingObject)
{
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
	/*if ((int)mListTile.size() == 0)
	{
		m_ObjectState = eObjectState::STATE_DEATH;
	}*/
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
	}

	for(int i = 0; i < mListTile.size(); ++i)
	{
		mListTile[i]->Update();
	}
}

void Bridge::Render(SPRITEHANDLE spriteHandle)
{
	m_HeadBreak->Render(spriteHandle, m_HeadTile->getPositionVec2(), ESpriteEffect::None, 0.0f, 1.0f, 1);
	m_TailBreak->Render(spriteHandle, m_TailTile->getPositionVec2() , ESpriteEffect::None, 0.0f, 1.0f, 1);
	for(int i = 0; i < mListTile.size(); ++i)
	{
		this->mListTile[i]->Render(spriteHandle);
	}
	
	
	
	
}

void Bridge::Release()
{
}

Bridge::~Bridge()
{
}