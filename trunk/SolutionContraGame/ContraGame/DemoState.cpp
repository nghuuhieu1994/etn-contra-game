#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{

	/*m_UnitTest.x = 400;
	m_UnitTest.y = 300;
	m_UnitTest.z = 0;*/


	//m_background = new Background();
	//m_background->Initialize("resources\\Map\\1\\1.map");
	
	m_Rambo = new Rambo(D3DXVECTOR3(100, 449, 1), eDirection::RIGHT, eObjectID::RAMBO);

#ifdef HIEU
	m_SniperStanding = new SniperStanding(D3DXVECTOR3(650, 130, 0), eDirection::LEFT, eObjectID::SNIPER_STANDING);
	m_SniperStanding->Initialize();

	m_snipperHiding = new SniperHiding(D3DXVECTOR3(750, 290, 0), eDirection::LEFT, eObjectID::SNIPER_HIDING);
	m_snipperHiding->Initialize();

	m_gifBullet = new GifBulletStatic(D3DXVECTOR3(500, 200, 1), eDirection::LEFT, eObjectID::GIF_BULLET_STATIC);
	m_gifBullet->Initialize();

	m_gifBulletMoving = new GifBulletMoving(D3DXVECTOR3(30, 200, 1), eDirection::LEFT, eObjectID::GIF_BULLET_MOVING);
	m_gifBulletMoving->Initialize();

	m_gunRotating = new GunRotating(D3DXVECTOR3(600, 200, 1), eDirection::LEFT, eObjectID::GUN_ROTATING);
	m_gunRotating->Initialize();

	m_bigGunRotating = new BigGunRotating(D3DXVECTOR3(800, 10, 1), eDirection::LEFT, eObjectID::BIG_GUN_ROTATING);
	m_bigGunRotating->Initialize();

	m_Enemy = new EnemyRun(D3DXVECTOR3(500, 100, 1), eDirection::LEFT, eObjectID::ENEMY_RUN);
	m_Enemy->Initialize();

	m_bossGun = new BossGun(D3DXVECTOR3(600, 100, 1), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_bossGun->Initialize();

	m_bossCenter = new BossCenter(D3DXVECTOR3(600, 50, 1), eDirection::LEFT, eObjectID::BOSS_CENTER);
	m_bossCenter->Initialize();  
#endif // HIEU


	BulletPoolManager::getInstance()->Initialize();

	/*m_VirtualObject = new VirtualObject(D3DXVECTOR3(96, 224, 1), 64, 64);
	m_VirtualObject->Initialize();*/
	/*SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Play();
	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();*/
	//m_listGameObjects.push_back(m_VirtualObject);

	//ReadMap("resources\\Map\\1\\map.xml");
	MapReader::getInstance()->ReadMap("resources\\Map\\1\\map.xml", &m_listGameObjects, &m_backgroundTile);
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{
	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());

	/*m_Rambo->UpdateAnimation();
	
	m_Rambo->UpdateMovement();

	for (std::list<Object*>::iterator it = m_listGameObjects.begin(); it != m_listGameObjects.end(); ++it)
	{
		m_Rambo->UpdateCollision(*it);
	}*/

	m_Rambo->Update(m_listGameObjects);

	BulletPoolManager::getInstance()->UpdateAnimation();
	BulletPoolManager::getInstance()->UpdateMovement();
	BulletPoolManager::getInstance()->Update();
#ifdef HIEU
	m_SniperStanding->UpdateCollision(m_Rambo);
	m_SniperStanding->UpdateAnimation();
	m_SniperStanding->Update();

	m_gifBullet->UpdateCollision(m_Rambo);
	m_gifBullet->UpdateAnimation();
	m_gifBullet->Update();

	m_gunRotating->UpdateCollision(m_Rambo);
	m_gunRotating->UpdateAnimation();
	m_gunRotating->Update();

	m_bigGunRotating->UpdateCollision(m_Rambo);
	m_bigGunRotating->UpdateAnimation();
	m_bigGunRotating->Update();


	
	m_gifBulletMoving->UpdateAnimation();
	m_gifBulletMoving->UpdateMovement();
	m_gifBulletMoving->UpdateCollision(m_Rambo);

	m_snipperHiding->UpdateAnimation();
	m_snipperHiding->Update();
	m_snipperHiding->UpdateCollision(m_Rambo);

	m_Enemy->UpdateAnimation();
	m_Enemy->UpdateMovement();

	m_bossGun->UpdateAnimation();
	m_bossGun->Update();

	m_bossCenter->UpdateAnimation();
	m_bossCenter->Update();  
#endif // HIEU



	
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	//m_background->Render(_lpDSpriteHandle);
	for (std::list<Object*>::iterator it = m_backgroundTile.begin(); it != m_backgroundTile.end(); it++)
	{
		(*it)->Render(_lpDSpriteHandle);
	}
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);

#ifdef HIEU
	m_gifBullet->Render(_lpDSpriteHandle);
	m_gifBulletMoving->Render(_lpDSpriteHandle);
	m_SniperStanding->Render(_lpDSpriteHandle);
	m_gunRotating->Render(_lpDSpriteHandle);
	m_bigGunRotating->Render(_lpDSpriteHandle);




	m_Enemy->Render(_lpDSpriteHandle);
	m_snipperHiding->Render(_lpDSpriteHandle);
	m_bossGun->Render(_lpDSpriteHandle);  
#endif // HIEU



}

void DemoState::Pause()
{

}

void DemoState::Resume()
{

}

void DemoState::Release()
{
	//for (std::list<Object*>::iterator it = m_listGameObjects.begin(); it != m_listGameObjects.end();)
	std::list<Object*>::iterator it;
	while((int)m_listGameObjects.size() > 0)
	{
		it = m_listGameObjects.begin();
		(*it)->Release();
		delete (*it);
		m_listGameObjects.remove(*it);
	}
	//m_listGameObjects.clear();
	BulletPoolManager::getInstance()->Release();
}