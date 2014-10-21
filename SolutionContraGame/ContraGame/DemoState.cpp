#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{

	m_UnitTest.x = 400;
	m_UnitTest.y = 300;
	m_UnitTest.z = 0;

	//m_background = new Background();
	//m_background->Initialize("resources\\Map\\1\\1.map");
	
	m_Rambo = new Rambo(D3DXVECTOR3(100, 100, 1), eDirection::RIGHT, eObjectID::RAMBO);
	m_SniperStanding = new SniperStanding(D3DXVECTOR3(650, 130, 0), eDirection::LEFT, eObjectID::SNIPER_STANDING);
	m_SniperStanding->Initialize();

	m_gifBullet = new GifBulletStatic(D3DXVECTOR3(500, 200, 1), eDirection::RIGHT, eObjectID::GIF_BULLET_STATIC);
	m_gifBullet->Initialize();

	m_gifBulletMoving = new GifBulletMoving(D3DXVECTOR3(30, 200, 1), eDirection::RIGHT, eObjectID::GIF_BULLET_MOVING);
	m_gifBulletMoving->Initialize();

	m_gunRotating = new GunRotating(D3DXVECTOR3(600, 200, 1), eDirection::RIGHT, eObjectID::GUN_ROTATING);
	m_gunRotating->Initialize();

	m_Enemy = new EnemyRun(D3DXVECTOR3(500, 100, 1), eDirection::LEFT, eObjectID::ENEMY_RUN);
	m_Enemy->Initialize();
	ReadMap();
}

void DemoState::ReadMap()
{
	CMarkup xml;
	xml.Load("resources\\Map\\1\\1a.map");
	xml.FindElem("Objects");
	xml.IntoElem();

	while (xml.FindElem("Object"))
	{
		GameObject *_GameObject;
		_GameObject = new GameObject();
		_GameObject->Deserialize(xml.GetSubDoc().c_str());
		_ListGameObjects.push_back(_GameObject);
	}
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{

	m_Rambo->UpdateAnimation();
	m_Rambo->UpdateMovement();
	m_Rambo->PrintState();

	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());

	m_SniperStanding->UpdateCollision(m_Rambo);
	m_SniperStanding->UpdateAnimation();
	m_SniperStanding->Update();

	m_gifBullet->UpdateCollision(m_Rambo);
	m_gifBullet->UpdateAnimation();
	m_gifBullet->Update();

	m_gunRotating->UpdateCollision(m_Rambo);
	m_gunRotating->UpdateAnimation();
	m_gunRotating->Update();

	m_gifBulletMoving->UpdateCollision(m_Rambo);
	m_gifBulletMoving->UpdateAnimation();
	m_gifBulletMoving->UpdateMovement();
	
	m_Enemy->UpdateAnimation();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	//m_background->Render(_lpDSpriteHandle);
	for (std::list<GameObject*>::iterator it = _ListGameObjects.begin(); it != _ListGameObjects.end(); it++)
	{
		if ((*it)->_Type == 0)
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MAP_1)->RenderAtFrame(_lpDSpriteHandle, D3DXVECTOR2((float)(*it)->_X, (float)(*it)->_Y), ESpriteEffect::None, 0.0f, 1.0f, 0.0f, 0xffffffff, (*it)->_ID); 
		}
	}
	SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GRID)->Render(_lpDSpriteHandle, D3DXVECTOR2(m_UnitTest.x, m_UnitTest.y), ESpriteEffect::None, 0.0f, 1.0f, 1.0f);
	m_gifBullet->Render(_lpDSpriteHandle);
	m_gifBulletMoving->Render(_lpDSpriteHandle);
	m_SniperStanding->Render(_lpDSpriteHandle);
	m_gunRotating->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	
	m_Enemy->Render(_lpDSpriteHandle);
}

void DemoState::Pause()
{

}

void DemoState::Resume()
{

}

void DemoState::Release()
{
	
}