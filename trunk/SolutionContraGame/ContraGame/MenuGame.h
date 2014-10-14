#ifndef __MENU_GAME_H__
#define __MENU_GAME_H__

//#include "CSpriteDx9.h"
#include "GameState.h"
#include "SpriteManager.h"
#include "StateManagerDx9.h"

class MenuGame : public GameState
{
private:
	bool m_IsDone;
	CSpriteDx9*			m_Icon;
	CSpriteDx9*			m_MenuBG;
	D3DXVECTOR3			m_IconPosition;
	D3DXVECTOR3			m_MenuPosition;
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