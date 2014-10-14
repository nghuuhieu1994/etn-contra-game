#include "TestSpriteState.h"

void TestSpriteState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	testSprite = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MAP_1);
}

float scalexxx = 1.0f;

void TestSpriteState::HandleInput()
{
	if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
	{
		scalexxx++;
	}
	if(CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
	{
		scalexxx--;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_RIGHT))
	{
		
	}
}

void TestSpriteState::Update()
{
	
}
void TestSpriteState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	testSprite->Render(_lpDSpriteHandle, D3DXVECTOR2(CENTERX, CENTERY), ESpriteEffect::None, 0.0f, (float)scalexxx, 1.0f);
}

void TestSpriteState::Pause()
{
	
}

void TestSpriteState::Resume()
{

}

void TestSpriteState::Release()
{
	testSprite = 0;
}