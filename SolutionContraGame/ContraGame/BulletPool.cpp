#include "BulletPool.h"

BulletPool* BulletPool::m_Instance = NULL;

BulletPool::BulletPool()
{

}

BulletPool* BulletPool::getInstance()
{
	if(BulletPool::m_Instance == NULL)
	{
		BulletPool::m_Instance = new BulletPool();
	}

	return BulletPool::m_Instance;
}

void BulletPool::Initialize()
{
	std::queue<Bullet*> queueOfRambo;
	for(int i = 0; i < BULLETOFRAMBO; ++i)
	{
		Bullet* tempBullet = new Bullet(D3DXVECTOR3(400.0f, 400.0f, 1.0f), eDirection::TOP, eObjectID::BULLET);	
		tempBullet->Initialize();
		queueOfRambo.push(tempBullet);
	}
	
	m_BulletPool.push_back(queueOfRambo);
}

Bullet* BulletPool::popBulletFromBulletPool(eIDTypeBullet _typebullet)
{
	switch(_typebullet)
	{
	case eIDTypeBullet::BULLETRAMBO:
		if(m_BulletPool[eIDTypeBullet::BULLETRAMBO].empty() == false)
		{
			Bullet* object = m_BulletPool[eIDTypeBullet::BULLETRAMBO].front();
			m_BulletPool[eIDTypeBullet::BULLETRAMBO].pop();

			return object;
		}
	default:
		return NULL;
	}
}

void BulletPool::addBulleToBulletPool(Bullet* _object)
{
	if(_object->getID() == eObjectID::BULLET)
	{
		Bullet* tempBullet = (Bullet*)_object;
		switch(tempBullet->getTypeBullet())
		{
		case eIDTypeBullet::BULLETRAMBO:
			m_BulletPool[eIDTypeBullet::BULLETRAMBO].push(tempBullet);
			break;
		default:
			break;
		}
	}
}

void BulletPool::releaseBulletPool()
{
	for(int i = 0; i < (int)m_BulletPool.size(); ++i)
	{
		while(m_BulletPool[i].empty() == false)
		{
			m_BulletPool[i].front()->Release();
			delete m_BulletPool[i].front();
			m_BulletPool[i].pop();
		}
	}

	m_BulletPool.clear();
	delete BulletPool::m_Instance;
	BulletPool::m_Instance = NULL;
}

BulletPool::~BulletPool()
{

}
