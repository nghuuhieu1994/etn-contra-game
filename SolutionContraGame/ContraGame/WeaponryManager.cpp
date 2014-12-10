#include "WeaponryManager.h"

WeaponryManager*	WeaponryManager::_instance = 0;

WeaponryManager*	WeaponryManager::getInstance()
{
	if (!_instance)
	{
		_instance = new WeaponryManager();
	}
	return _instance;
}

void WeaponryManager::AddElement(DynamicObject* object)
{
	object->Initialize();
	object->getPhysic()->setAccelerate(D3DXVECTOR2(0.0f, ACCEL_WEAPONRY_Y));
	object->getPhysic()->setVelocity(D3DXVECTOR2(VELOC_WEAPONRY_X, VELOC_WEAPONRY_Y));
	m_ListWeaponry.push_back(object);
}

void WeaponryManager::Update()
{
	if (m_ListWeaponry.empty() != true)
	{
		for (list<DynamicObject*>::iterator i = m_ListWeaponry.begin(); i != m_ListWeaponry.end(); )
		{

			(*i)->UpdateAnimation();
			(*i)->UpdateMovement();
			(*i)->Update();

			
			if (CGlobal::Rambo_X - (*i)->getPositionVec2().x > SCREEN_WIDTH / 2)
			{
				//(*i)->Release();
				SAFE_DELETE(*i);
				i = m_ListWeaponry.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

void WeaponryManager::UpdateCollision(Object* checkingObject)
{
	if (m_ListWeaponry.empty() != true)
	{
		for (list<DynamicObject*>::iterator i = m_ListWeaponry.begin(); i != m_ListWeaponry.end();)
		{
			(*i)->UpdateCollision(checkingObject);

			if ((*i)->getObjectState() == STATE_DEATH)
			{
				SAFE_DELETE(*i);
				i = m_ListWeaponry.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

void WeaponryManager::Render(SPRITEHANDLE spriteHandle)
{
	if (m_ListWeaponry.empty() != true)
	{
		for (list<DynamicObject*>::iterator i = m_ListWeaponry.begin(); i != m_ListWeaponry.end(); i++)
		{
			(*i)->Render(spriteHandle);
		}
	}
}

void WeaponryManager::Release()
{
	for (list<DynamicObject*>::iterator i = m_ListWeaponry.begin(); i != m_ListWeaponry.end(); i++)
	{
		(*i)->Release();
		SAFE_DELETE(*i);
	}
	m_ListWeaponry.clear();
}