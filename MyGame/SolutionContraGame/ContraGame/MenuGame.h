#ifndef __MENU_GAME_H__
#define __MENU_GAME_H__
//#include "CSpriteDx9.h"
#include "SpriteManager.h"
#include "StateManagerDx9.h"
#include "GameState.h"

class MenuGame : public GameState
{
private:
	CSpriteDx9*			m_MenuBG;
	CSpriteDx9*			m_Icon;

	D3DXVECTOR3			m_MenuPosition;
	D3DXVECTOR3			m_IconPosition;

	bool m_IsDone;

public:
	MenuGame(eIDStateGame ID) : GameState(ID) {} 
	~MenuGame(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};


#endif