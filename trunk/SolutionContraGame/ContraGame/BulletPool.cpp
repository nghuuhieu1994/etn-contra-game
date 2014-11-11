#include "BulletPool.h"

BulletPool* BulletPool::m_Instance = 0;

BulletPool::BulletPool()
{

}

BulletPool* BulletPool::getInstance()
{
	if(BulletPool::m_Instance == 0)
	{
		BulletPool::m_Instance = new BulletPool();
	}

	return BulletPool::m_Instance;
}

void BulletPool::Initialize()
{
	std::queue<Bullet*> queueOfRambo;

	for(int i = 0; i < QUALITY_OF_DEFAULT_BULLET_RAMBO; ++i)
	{
		DefaultBullet* tempBullet = new DefaultBullet(D3DXVECTOR3(400.0f, 300.0f, 1.0f), eDirection::TOP, eObjectID::BULLET);	
		tempBullet->Initialize();
		queueOfRambo.push(tempBullet);
	}
	
	m_BulletPool.push_back(queueOfRambo);
}

Bullet* BulletPool::popBulletFromBulletPool(eIDTypeBullet _typebullet, D3DXVECTOR3 _position, eDirectAttack _directionAttack)
{
	switch(_typebullet)
	{
	case eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO:
		if(m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].empty() == false)
		{
			DefaultBullet* object = (DefaultBullet*) m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].front();
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->setDirectAttack(_directionAttack);
			object->ResetLivingTime();
			m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].pop();

			return object;
		}
	default:
		return 0;
	}
}

void BulletPool::addBulleToBulletPool(Bullet* _object)
{
	if(_object->getID() == eObjectID::BULLET)
	{
		switch(_object->getTypeBullet())
		{
		case eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO:
			_object->reset();
			m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].push((DefaultBullet*) _object);
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
	BulletPool::m_Instance = 0;
}

BulletPool::~BulletPool()
{

}