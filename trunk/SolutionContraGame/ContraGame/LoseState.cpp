#include "LoseState.h"
#include "PlayScene.h"
#include "MenuGame.h"
#include <fstream>

using namespace std;

LoseState::LoseState(eIDSceneGame _ID, int _currentStage) : GameScene(_ID)
{
	m_currentStage = _currentStage;
	m_Icon = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ICON));
	m_IconPosition.x = 110;
	m_IconPosition.y = 184;
	m_IconPosition.z = 1;
}

void LoseState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::s_theme_gameover)->Repeat();
	D3DXCreateFont(_lpDirectDevice, 30, 16, 1, D3DX_DEFAULT, false, 0, 0, 0, 0, "Arial", &m_Font);
}

void LoseState::HandleInput()
{

}

void LoseState::Update()
{
	if(CInputDx9::getInstance()->IsKeyPress(DIK_DOWN))
	{
		if(m_IconPosition.y == 184)
			m_IconPosition.y -= 32;
		else
			m_IconPosition.y += 32;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_UP))
	{
		if(m_IconPosition.y == 184)
			m_IconPosition.y -= 32;
		else
			m_IconPosition.y += 32;
	}
	if(CInputDx9::getInstance()->IsKeyPress(DIK_RETURN))
	{
		SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::s_theme_gameover)->Stop();

		if(m_IconPosition.y == 184)
		{
			SceneManagerDx9::getInstance()->ReplaceBy(new PlayScene(eIDSceneGame::INTRO, m_currentStage));
			PlayScene::setScore(0);
		}
		if(m_IconPosition.y == 152)
		{
			SceneManagerDx9::getInstance()->ReplaceBy(new MenuGame(eIDSceneGame::INTRO));
			PlayScene::setScore(0);
		}
	}
}

void LoseState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	LPSTR label;
	
	label = "HI";
	RECT rect;
	rect.left = 100;
	rect.top = 100;
	rect.right = 400;
	rect.bottom = 250;
	D3DXMATRIX oldMatrix;
	D3DXMATRIX newMatrix;
	D3DXMatrixIdentity(&newMatrix);
	_lpDSpriteHandle->GetTransform(&oldMatrix);
	_lpDSpriteHandle->SetTransform(&newMatrix);
	m_Font->DrawTextA(_lpDSpriteHandle, label, -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));

	LPSTR score;
	char buff[100];
	fstream file("resources\\Map\\MenuGame\\highscore", ios::in);
	int rank;
	file >> rank;
	file.close();
	sprintf_s(buff, "%d", rank);
	score = buff;
	rect.left = 150;
	rect.top = 100;
	rect.right = 448;
	rect.bottom = 250;
	m_Font->DrawTextA(_lpDSpriteHandle, score, -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));

	rect.left = 140;
	rect.top = 200;
	rect.right = 400;
	rect.bottom = 350;
	m_Font->DrawTextA(_lpDSpriteHandle, "GAME OVER", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));

	rect.left = 140;
	rect.top = 250;
	rect.right = 400;
	rect.bottom = 350;
	m_Font->DrawTextA(_lpDSpriteHandle, "Continue", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));

	rect.left = 140;
	rect.top = 280;
	rect.right = 400;
	rect.bottom = 350;
	m_Font->DrawTextA(_lpDSpriteHandle, "Quit Game", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));

	_lpDSpriteHandle->SetTransform(&oldMatrix);

	m_Icon->Render(_lpDSpriteHandle, D3DXVECTOR2(m_IconPosition.x, m_IconPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_IconPosition.z);
}

void LoseState::Pause()
{

}

void LoseState::Resume()
{

}

void LoseState::Release()
{

}

LoseState::~LoseState(void)
{
}
