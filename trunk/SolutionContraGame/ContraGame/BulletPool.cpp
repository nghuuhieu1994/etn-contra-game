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
	std::queue<Bullet*> queuDefaultBulletOfRambo;
	for(int i = 0; i < QUALITY_OF_DEFAULT_BULLET_RAMBO; ++i)
	{
		DefaultBullet* tempBullet = new DefaultBullet(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::BULLET_RAMBO);	
		tempBullet->Initialize();
		queuDefaultBulletOfRambo.push(tempBullet);
	}

	m_BulletPool.push_back(queuDefaultBulletOfRambo);
	std::queue<Bullet*> queueRedBulletOfRambo;
	for(int i = 0; i < QUALITY_OF_RED_BULLET_RAMBO; ++i)
	{
		RedBullet* tempBullet = new RedBullet(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::BULLET_RAMBO);
		tempBullet->Initialize();
		queueRedBulletOfRambo.push(tempBullet);
	}
	m_BulletPool.push_back(queueRedBulletOfRambo);

	std::queue<Bullet*> queueFireBulletOfRambo;
	for(int i = 0; i < QUALITY_OF_RED_BULLET_RAMBO; ++i)
	{
		FireBullet* tempBullet = new FireBullet(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::BULLET_RAMBO);
		tempBullet->Initialize();
		queueFireBulletOfRambo.push(tempBullet);
	}
	m_BulletPool.push_back(queueFireBulletOfRambo);
}

Bullet* BulletPool::popBulletFromBulletPool(eIDTypeBullet _typebullet, D3DXVECTOR3 _position, D3DXVECTOR2 _velocity, float _factor)
{
	switch(_typebullet)
	{
	case eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO:
		if(m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].empty() == false)
		{
			DefaultBullet* object = (DefaultBullet*) m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].front();
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].pop();

			return object;
		}
		break;
	case eIDTypeBullet::RED_BULLET_OF_RAMBO:
		if(m_BulletPool[eIDTypeBullet::RED_BULLET_OF_RAMBO].empty() == false)
		{
			RedBullet* object = (RedBullet*) m_BulletPool[eIDTypeBullet::RED_BULLET_OF_RAMBO].front();
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			m_BulletPool[eIDTypeBullet::RED_BULLET_OF_RAMBO].pop();

			return object;
		}
		break;
	case eIDTypeBullet::FIRE_BULLET_OF_RAMBO:
		if(m_BulletPool[eIDTypeBullet::FIRE_BULLET_OF_RAMBO].empty() == false)
		{
			FireBullet* object = (FireBullet*) m_BulletPool[eIDTypeBullet::FIRE_BULLET_OF_RAMBO].front();
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			object->setVelocityOrigin(_velocity);
			object->setPositionOfOrigin(_position);
			m_BulletPool[eIDTypeBullet::FIRE_BULLET_OF_RAMBO].pop();

			return object;
		}
		break;
	default:
		return 0;
	}
}

void BulletPool::addBulleToBulletPool(Bullet* _object)
{
	if(_object->getID() == eObjectID::BULLET_RAMBO)
	{
		switch(_object->getTypeBullet())
		{
		case eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO:
			_object->reset();
			m_BulletPool[eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO].push((DefaultBullet*) _object);
			break;
		case eIDTypeBullet::RED_BULLET_OF_RAMBO:
			_object->reset();
			m_BulletPool[eIDTypeBullet::RED_BULLET_OF_RAMBO].push((RedBullet*) _object);
			break;
		case eIDTypeBullet::FIRE_BULLET_OF_RAMBO:
			_object->reset();
			m_BulletPool[eIDTypeBullet::FIRE_BULLET_OF_RAMBO].push((RedBullet*) _object);
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
