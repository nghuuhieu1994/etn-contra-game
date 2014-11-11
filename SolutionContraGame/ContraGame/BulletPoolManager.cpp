#include "BulletPoolManager.h"

BulletPoolManager* BulletPoolManager::m_Instance = 0;

BulletPoolManager::BulletPoolManager()
{

}

void BulletPoolManager::Initialize()
{
	BulletPool::getInstance()->Initialize();
}

void BulletPoolManager::addBulletIntoList(eIDTypeBullet typeBullet, D3DXVECTOR3 position, eDirectAttack _directionAttack)
{
	this->m_ListBulletInGame.push_back((DefaultBullet*)BulletPool::getInstance()->popBulletFromBulletPool(typeBullet, position, _directionAttack));
}

void BulletPoolManager::popBulletFromList()
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin() ; i != this->m_ListBulletInGame.end(); )
	{
		if((*i)->getObjectState() == eObjectState::STATE_DEATH)
		{
			BulletPool::getInstance()->addBulleToBulletPool((*i));
			//this->m_ListBulletInGame.remove((*i));
			i = this->m_ListBulletInGame.erase(i);
		}
		else
		{
			++i;
		}
	}
}

BulletPoolManager* BulletPoolManager::getInstance()
{
	if(BulletPoolManager::m_Instance == 0)
	{
		BulletPoolManager::m_Instance = new BulletPoolManager();
	}

	return BulletPoolManager::m_Instance;
}

void BulletPoolManager::Update()
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin(); i != this->m_ListBulletInGame.end(); ++i)
	{
		(*i)->Update();
	}
	popBulletFromList();
}

void BulletPoolManager::UpdateAnimation()
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin(); i != this->m_ListBulletInGame.end(); ++i)
	{
		(*i)->UpdateAnimation();
	}
}

void BulletPoolManager::UpdateMovement()
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin(); i != this->m_ListBulletInGame.end(); ++i)
	{
		(*i)->UpdateMovement();
	}
}

void BulletPoolManager::UpdateCollision(Object* checkingObject)
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin(); i != this->m_ListBulletInGame.end(); ++i)
	{
		(*i)->UpdateCollision(checkingObject);
	}
}

void BulletPoolManager::Render(SPRITEHANDLE spriteHandler)
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin(); i != this->m_ListBulletInGame.end(); ++i)
	{
		(*i)->Render(spriteHandler);
	}
}

void BulletPoolManager::Release()
{
	for(std::list<Bullet*>::iterator i = this->m_ListBulletInGame.begin(); i != this->m_ListBulletInGame.end(); ++i)
	{
		(*i)->Release();
		delete (*i);
	}
	BulletPool::getInstance()->releaseBulletPool();
	this->m_ListBulletInGame.clear();
	delete BulletPoolManager::m_Instance;
	BulletPoolManager::m_Instance = 0;
}

BulletPoolManager::~BulletPoolManager()
{

}
