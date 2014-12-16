#include "MenuGame.h"
#include "DemoState.h"
#include "PlayScene.h"

void MenuGame::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::s_them_menu)->Repeat();

	m_MenuBG = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MENUBG));
	m_Icon = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ICON));

	m_MenuPosition.x = (float)(SCREEN_WIDTH/2 + m_MenuBG->getMyTexture()->m_Width / 2);

	//m_MenuPosition.x = 0;
	m_MenuPosition.y = SCREEN_HEIGHT / 2;
	m_MenuPosition.z = 0;
	m_IconPosition.x = (float)(SCREEN_WIDTH/2 + m_MenuBG->getMyTexture()->m_Width / 2 + 88);
	m_IconPosition.y = 140;
	m_IconPosition.z = 1;

	m_IsDone = false;
}

void MenuGame::HandleInput()
{
	if(m_IsDone == true)
	{
		if(CInputDx9::getInstance()->IsKeyPress(DIK_DOWN))
		{
			if(m_IconPosition.y == 140)
				m_IconPosition.y -= 32;
			else
				m_IconPosition.y += 32;
		}
		if(CInputDx9::getInstance()->IsKeyPress(DIK_UP))
		{
			if(m_IconPosition.y == 140)
				m_IconPosition.y -= 32;
			else
				m_IconPosition.y += 32;
		}

		if(CInputDx9::getInstance()->IsKeyPress(DIK_RETURN))
		{
			if(m_IconPosition.y == 140)
			{
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::s_them_menu)->Stop();
				SceneManagerDx9::getInstance()->ReplaceBy(new HighScoreState(eIDSceneGame::INTRO, 1));
				PlayScene::setScore(0);
			}
		}

	}
}

void MenuGame::Update()
{
	if(m_MenuPosition.x > 0)
	{
		m_MenuPosition.x --;
		m_IconPosition.x --;
	}
	else
		if(m_MenuPosition.x <= 0)
		{
			m_IsDone = true;
		}
}

void MenuGame::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_MenuBG->Render(_lpDSpriteHandle, D3DXVECTOR2(m_MenuPosition.x, m_MenuPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_MenuPosition.z);
	m_Icon->Render(_lpDSpriteHandle, D3DXVECTOR2(m_IconPosition.x, m_IconPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_IconPosition.z);
}

void MenuGame::Pause()
{
}

void MenuGame::Resume()
{
}

void MenuGame::Release()
{
}
