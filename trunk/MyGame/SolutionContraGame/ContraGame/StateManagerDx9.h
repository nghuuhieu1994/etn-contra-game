#ifndef __STATEMANAGERDX9_H__
#define __STATEMANAGERDX9_H__
#include "GameState.h"
#include "CGameLog.h"
#include "CGlobal.h"
#include <vector>
class GameState;

class StateManagerDx9
{
private:
	// private constructor
	StateManagerDx9() {}
	// privatr destructor
	~StateManagerDx9() {}
	// vector contain all state
	vector<GameState*> ListGameState;
	// a static pointer to instance
	static StateManagerDx9* s_Instance;
	// lpD
	LPDIRECT3DDEVICE9		m_lpDirectDevice;

public:
	// get Instrance
	static StateManagerDx9* getInstance();
	// set lpD
	void setDirectDevice(const LPDIRECT3DDEVICE9& lpDirectDevice);
	// init game
	void Initialize();
	// update this state
	void UpdateHanleInput(CInputDx9* input);
	// update action in this state
	void Update(CGameTimeDx9* gameTime);
	// render all sprite
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	// add an element to vector
	void AddElement(GameState* gameState);
	// exit element
	void ExitState();
	// replace state
	void ReplaceBy(GameState* gameState);
	// clear all state
	void ClearAll();
};

#endif