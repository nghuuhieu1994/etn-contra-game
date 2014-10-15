#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{

	m_UnitTest.x = 400;
	m_UnitTest.y = 300;
	m_UnitTest.z = 0;

	m_background = new Background();
	//m_background->Initialize("resources\\Map\\1\\1.map");
	
	m_Rambo = new Rambo(D3DXVECTOR3(100, 100, 1), eDirection::RIGHT, eObjectID::RAMBO);
	m_SniperStanding = new SniperStanding(D3DXVECTOR3(650, 130, 0), eDirection::LEFT, eObjectID::SNIPER_STANDING);
	m_SniperStanding->Initialize();
	m_gifBullet = new GifBulletStatic(D3DXVECTOR3(500, 200, 1), eDirection::RIGHT, eObjectID::GIF_BULLET_STATIC);
	m_gifBullet->Initialize();
	m_Flyersin = new Flyer_Sin(D3DXVECTOR3(30, 200, 1), eDirection::RIGHT, eObjectID::FLYER_SIN);
	m_Flyersin->Initialize();
	m_gunRotating = new GunRotating(D3DXVECTOR3(600, 200, 1), eDirection::RIGHT, eObjectID::GUN_ROTATING);
	m_gunRotating->Initialize();
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{

	/*m_Rambo->HandleInput();*/
	m_Rambo->UpdateAnimation();
	m_Rambo->UpdateMovement();
	m_Rambo->PrintState();
	//SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();
	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());

	m_SniperStanding->UpdateCollision(m_Rambo);
	m_SniperStanding->UpdateAnimation();
	m_SniperStanding->Update();

	m_gifBullet->UpdateAnimation();
	m_gifBullet->Update();
	m_gunRotating->UpdateAnimation();
	m_gunRotating->Update();
	m_Flyersin->UpdateAnimation();
	m_Flyersin->UpdateMovement();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_background->Render(_lpDSpriteHandle);
	//SpriteManager::getInstance()->getSprite(eSpriteID::GRID)->Render(_lpDSpriteHandle, D3DXVECTOR2(m_UnitTest.x, m_UnitTest.y), ESpriteEffect::None, 0.0f, 1.0f, 1.0f);
	m_gifBullet->Render(_lpDSpriteHandle);
	m_Flyersin->Render(_lpDSpriteHandle);
	m_SniperStanding->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	m_gunRotating->Render(_lpDSpriteHandle);
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