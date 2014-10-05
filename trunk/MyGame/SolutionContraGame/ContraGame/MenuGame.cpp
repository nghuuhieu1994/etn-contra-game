#include "MenuGame.h"
#include "DemoState.h"
void MenuGame::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_MenuBG = SpriteManager::getInstance()->getSprite(eSpriteID::MENUBG);
	m_Icon = SpriteManager::getInstance()->getSprite(eSpriteID::ICON);

	m_MenuPosition.x = WIDTH + m_MenuBG->getMyTexture()->m_Width / 2 - 300;

	//m_MenuPosition.x = 0;
	m_MenuPosition.y = HEIGHT / 2;
	m_MenuPosition.z = 0;
	m_IconPosition.x = 80 + WIDTH + m_MenuBG->getMyTexture()->m_Width / 2 - 300;
	m_IconPosition.y = 215;
	m_IconPosition.z = 1;

	m_IsDone = false;
}

void MenuGame::HandleInput()
{
	if(m_IsDone == true)
	{
		if(CInputDx9::getInstance()->IsKeyPress(DIK_DOWN))
		{
			if(m_IconPosition.y == 215)
				m_IconPosition.y -= 32;
			else
				m_IconPosition.y += 32;
		}
		if(CInputDx9::getInstance()->IsKeyPress(DIK_UP))
		{
			if(m_IconPosition.y == 215)
				m_IconPosition.y -= 32;
			else
				m_IconPosition.y += 32;
		}

		if(CInputDx9::getInstance()->IsKeyPress(DIK_SPACE))
		{
			if(m_IconPosition.y == 215)
			{
				StateManagerDx9::getInstance()->ReplaceBy(new DemoState(eIDStateGame::INTRO));
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
		if(m_MenuPosition.x == 0)
		{
			m_IsDone = true;
		}
}

void MenuGame::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_MenuBG->Render(_lpDSpriteHandle, D3DXVECTOR2(m_MenuPosition.x, m_MenuPosition.y), eSpriteEffect::None, 0.0f, 1.0f, m_MenuPosition.z);
	m_Icon->Render(_lpDSpriteHandle, D3DXVECTOR2(m_IconPosition.x, m_IconPosition.y), eSpriteEffect::None, 0.0f, 1.0f, m_IconPosition.z);
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
