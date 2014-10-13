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
	m_gun1 = new Gun_1(D3DXVECTOR3(500, 200, 1), eDirection::RIGHT, eObjectID::GUN_1);
	m_gun1->Initialize();
	m_Flyersin = new Flyer_Sin(D3DXVECTOR3(30, 300, 1), eDirection::RIGHT, eObjectID::FLYER_SIN);
	m_Flyersin->Initialize();
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
	//SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();
	Camera::getInstance()->UpdateCamera(&m_Rambo->getPhysic()->getPositionVec3());

	m_SniperStanding->UpdateCollision(m_Rambo);
	m_SniperStanding->UpdateAnimation();

	m_gun1->UpdateAnimation();
	m_Flyersin->UpdateAnimation();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_background->Render(_lpDSpriteHandle);
	//SpriteManager::getInstance()->getSprite(eSpriteID::GRID)->Render(_lpDSpriteHandle, D3DXVECTOR2(m_UnitTest.x, m_UnitTest.y), eSpriteEffect::None, 0.0f, 1.0f, 1.0f);
	m_Rambo->Render(_lpDSpriteHandle);
	m_SniperStanding->Render(_lpDSpriteHandle);
	m_gun1->Render(_lpDSpriteHandle);
	m_Flyersin->Render(_lpDSpriteHandle);
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