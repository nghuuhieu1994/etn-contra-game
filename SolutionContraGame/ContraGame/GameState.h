#ifndef __GAMESTATE_H__
#define	__GAMESTATE_H__

#include "CGameLog.h"
#include "CGameTimeDx9.h"
#include "CGlobal.h"
#include "CInputDx9.h"
#include "StateManagerDx9.h"

class StateManagerDx9;

class GameState
{
protected:
	eIDStateGame eID;
public:
	GameState(eIDStateGame ID){eID = ID;}
	virtual void HandleInput() = 0;
	virtual void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice) = 0;
	virtual void Pause() = 0;
	virtual void Release() = 0;
	virtual void Render(LPD3DXSPRITE _lpDSpriteHandle) = 0;
	virtual void Resume() = 0;
	virtual void Update() = 0;
	virtual ~GameState() {}
};

#endif