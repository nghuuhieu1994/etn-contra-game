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
	
	StateManagerDx9() {}
	
	~StateManagerDx9() {}
	
	vector<GameState*> m_ListGameState;
	
	static StateManagerDx9* s_Instance;
	
	LPDIRECT3DDEVICE9		m_lpDirectDevice;

public:
	
	static StateManagerDx9* getInstance();
	
	void setDirectDevice(const LPDIRECT3DDEVICE9& lpDirectDevice);
	
	void Initialize();
	
	void HandleInput();
	
	void Update();
	
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	
	void AddElement(GameState* gameState);
	
	void ExitState();
	
	void ReplaceBy(GameState* gameState);
	
	void ClearAll();
};

#endif