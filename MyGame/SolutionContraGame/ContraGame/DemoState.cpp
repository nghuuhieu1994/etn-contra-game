#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
		//texture->LoadContent(m_lpDirect3DDevice, "resources\\Character\\Bill\\bullet.png", 1, 1, 1, 0xffff00ff);
	texture = SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_JUMP);
		
		m_UnitTest.x = 400;
		m_UnitTest.y = 300;
		m_UnitTest.z = 0;
		m_testSpriteEffect = eSpriteEffect::None;
}

void DemoState::HandleInput()
{
}
void DemoState::Update()
{
	texture->UpdateAnimation(100);
}
void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
		texture->Render(_lpDSpriteHandle, D3DXVECTOR2(m_UnitTest.x, m_UnitTest.y), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
}
void DemoState::Pause()
{}
void DemoState::Resume()
{}
void DemoState::Release()
{
	texture = NULL;
}