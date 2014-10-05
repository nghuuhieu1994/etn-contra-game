#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{

	m_UnitTest.x = 400;
	m_UnitTest.y = 300;
	m_UnitTest.z = 0;

	m_background = new Background();
	m_background->Initialize("resources\\Map\\1\\1.map");
}

void DemoState::HandleInput()
{

}

void DemoState::Update()
{
	if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		m_UnitTest.x++;
	}

	if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
	{
		
		m_UnitTest.x--;
	}

	if(m_UnitTest.x < 0)
	{
		m_UnitTest.x= 0;
	}

	Camera::getInstance()->UpdateCamera(&m_UnitTest);
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_background->Render(_lpDSpriteHandle);
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