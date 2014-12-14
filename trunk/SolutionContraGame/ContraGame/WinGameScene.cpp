#include "WinGameScene.h"
#include "DemoState.h"

void WinGameScene::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_WinSceneBG = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WINSCENE);

	//m_WinScenePosition.x = (float)(SCREEN_WIDTH/2 + m_WinSceneBG->getMyTexture()->m_Width / 2);
	m_WinScenePosition.x = 0;
	m_WinScenePosition.y = SCREEN_HEIGHT / 2;
	m_WinScenePosition.z = 1;
	m_isDone = false;
}

void WinGameScene::HandleInput()
{
	if(m_isDone == true)
	{
		if(CInputDx9::getInstance()->IsKeyPress(DIK_ESCAPE))
		{
			//Exit game
			std::exit(1);
			
		}
		if(CInputDx9::getInstance()->IsKeyPress(DIK_RETURN))
		{
			SceneManagerDx9::getInstance()->ReplaceBy(new DemoState(eIDSceneGame::DEMO, 1));
		}

	}
}

void WinGameScene::Update()
{
	if(m_WinScenePosition.x >= 0 && m_WinScenePosition.x < SCREEN_WIDTH / 2)
	{
		m_WinScenePosition.x ++;
	}
	else if(m_WinScenePosition.x == SCREEN_WIDTH / 2)
	{
		m_isDone = true;
	}
}

void WinGameScene::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_WinSceneBG->Render(_lpDSpriteHandle, D3DXVECTOR2(m_WinScenePosition.x, m_WinScenePosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_WinScenePosition.z);
}

void WinGameScene::Pause()
{
}
void WinGameScene::Resume()
{
}

void WinGameScene::Release()
{
	m_WinSceneBG->Release();
}
