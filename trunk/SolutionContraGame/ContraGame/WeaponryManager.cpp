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
		for (int i = 0; i < (int)m_ListWeaponry.size(); i++)
		{
			m_ListWeaponry[i]->UpdateAnimation();
			m_ListWeaponry[i]->UpdateMovement();
			m_ListWeaponry[i]->Update();
		}
	}
}

void WeaponryManager::UpdateCollision(Object* checkingObject)
{
	if (m_ListWeaponry.empty() != true)
	{
		for (int i = 0; i < (int)m_ListWeaponry.size(); i++)
		{
			m_ListWeaponry[i]->UpdateCollision(checkingObject);
		}
	}
}

void WeaponryManager::Render(SPRITEHANDLE spriteHandle)
{
	if (m_ListWeaponry.empty() != true)
	{
		for (int i = 0; i < (int)m_ListWeaponry.size(); i++)
		{
			m_ListWeaponry[i]->Render(spriteHandle);
		}
	}
}

void WeaponryManager::Release()
{
	for (int i = 0; i < (int)m_ListWeaponry.size(); i++)
	{
		m_ListWeaponry[i]->Release();
	}
	while (m_ListWeaponry.empty() != true)
	{
		m_ListWeaponry.pop_back();
	}
}