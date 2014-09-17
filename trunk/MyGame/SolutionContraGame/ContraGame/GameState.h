#ifndef __GAMESTATE_H__
#define	__GAMESTATE_H__
#include "CGameTimeDx9.h"
#include "CGameLog.h"
#include "CGlobal.h"
#include "CInputDx9.h"
#include "StateManagerDx9.h"

class StateManagerDx9;

class GameState
{
protected:
	// ID for every StateGame
	eIDStateGame eID;	
	
public:
	// constructor
	GameState(eIDStateGame ID){eID = ID;}
	// destructor
	virtual ~GameState() {}
	// initialize
	virtual void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice) = 0;
	// Update all input event
	virtual void UpdateHandleInput(CInputDx9* Input) = 0;
	// update all action in game
	virtual void Update(CGameTimeDx9* gameTime) = 0;
	// render sprite to screen
	virtual void Render(LPD3DXSPRITE _lpDSpriteHandle) = 0;
	// pause this state
	virtual void Pause() = 0;
	// resume after pause
	virtual void Resume() = 0;
	// Release this state
	virtual void Release() = 0;
};

#endif