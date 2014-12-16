#include "HighScoreState.h"
#include "PlayScene.h"

#include <fstream>

using namespace std;

void HighScoreState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	D3DXCreateFont(_lpDirectDevice, 30, 16, 1, D3DX_DEFAULT, false, 0, 0, 0, 0, "Arial", &m_Font);
	coolDonwChange = 0;
}

void HighScoreState::HandleInput()
{
	
}

void HighScoreState::Update()
{
	coolDonwChange += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (coolDonwChange > 5000)
	{
		if (NextStage > 0)
		{
			SceneManagerDx9::getInstance()->AddElement(new PlayScene(eIDSceneGame::DEMO, NextStage)); 
		}
		else
		{
			SceneManagerDx9::getInstance()->AddElement(new MenuGame(eIDSceneGame::DEMO)); 
		}
	}
}

void HighScoreState::Render(LPD3DXSPRITE _lpDSpriteHandle)
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
	if (NextStage == -1)
	{
		rect.left = 200;
		rect.top = 250;
		rect.right = 400;
		rect.bottom = 350;
		m_Font->DrawTextA(_lpDSpriteHandle, "TO BE CONTINUED", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
	}
	if (NextStage == 0)
	{
		rect.left = 200;
		rect.top = 250;
		rect.right = 400;
		rect.bottom = 350;
		m_Font->DrawTextA(_lpDSpriteHandle, "LOSE", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
	}
	if (NextStage == 1)
	{
		rect.left = 200;
		rect.top = 200;
		rect.right = 400;
		rect.bottom = 300;
		m_Font->DrawTextA(_lpDSpriteHandle, "STAGE 1", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
		rect.left = 200;
		rect.top = 250;
		rect.right = 400;
		rect.bottom = 350;
		m_Font->DrawTextA(_lpDSpriteHandle, "JUNGLE", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
	}
	if (NextStage == 2)
	{
		rect.left = 200;
		rect.top = 200;
		rect.right = 400;
		rect.bottom = 300;
		m_Font->DrawTextA(_lpDSpriteHandle, "STAGE 2", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
		rect.left = 180;
		rect.top = 250;
		rect.right = 400;
		rect.bottom = 350;
		m_Font->DrawTextA(_lpDSpriteHandle, "WATER FALL", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
	}
	if (NextStage == 3)
	{
		rect.left = 200;
		rect.top = 200;
		rect.right = 400;
		rect.bottom = 300;
		m_Font->DrawTextA(_lpDSpriteHandle, "STAGE 3", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
		rect.left = 100;
		rect.top = 250;
		rect.right = 400;
		rect.bottom = 350;
		m_Font->DrawTextA(_lpDSpriteHandle, "SNOW FIELD", -1, &rect, D3DFMT_UNKNOWN, D3DCOLOR_XRGB(255, 255, 255));
	}
	_lpDSpriteHandle->SetTransform(&oldMatrix);
}

void HighScoreState::Pause()
{
}

void HighScoreState::Resume()
{
}

void HighScoreState::Release()
{
}
