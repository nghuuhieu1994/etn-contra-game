#include "DemoState.h"


void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	
	m_Rambo = new Rambo(D3DXVECTOR3(100, 500, 1), eDirection::RIGHT, eObjectID::RAMBO);


	BulletPoolManager::getInstance()->Initialize();
	LedObject::getStaticInstance()->Initialize();
	MapReader::getInstance()->ReadMap("resources\\Map\\1\\map.xml", &m_listGameObjects, &m_backgroundTile, &m_ledObject);
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{
	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());

	LedObject::getStaticInstance()->UpdateAnimation();

	m_Rambo->Update(m_listGameObjects);

	BulletPoolManager::getInstance()->UpdateAnimation();
	BulletPoolManager::getInstance()->UpdateMovement();
	BulletPoolManager::getInstance()->Update();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	for (std::list<Object*>::iterator it = m_backgroundTile.begin(); it != m_backgroundTile.end(); it++)
	{
		(*it)->Render(_lpDSpriteHandle);
	}
	for(auto it = m_ledObject.begin(); it != m_ledObject.end(); ++it)
	{
		(*it)->Render(_lpDSpriteHandle);
	}
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MEDAL)->RenderWithoutTransform(_lpDSpriteHandle, D3DXVECTOR2(40, 414), ESpriteEffect::None, 0.0f, 1.0f, 1.0f);
	SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MEDAL)->RenderWithoutTransform(_lpDSpriteHandle, D3DXVECTOR2(64, 414), ESpriteEffect::None, 0.0f, 1.0f, 1.0f);
	m_Rambo->Render(_lpDSpriteHandle);
}

void DemoState::Pause()
{

}

void DemoState::Resume()
{

}

void DemoState::Release()
{
	
	std::list<Object*>::iterator it;
	while((int)m_listGameObjects.size() > 0)
	{
		it = m_listGameObjects.begin();
		(*it)->Release();
		delete (*it);
		m_listGameObjects.remove(*it);
	}
	
	BulletPoolManager::getInstance()->Release();
}