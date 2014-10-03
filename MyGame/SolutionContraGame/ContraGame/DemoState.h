#ifndef __DEMO_STATE_H__
#define __DEMO_STATE_H__
#include "GameState.h"
#include "StateManagerDx9.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"

class DemoState : public GameState
{
private:
	D3DXVECTOR3			m_UnitTest;
	CSpriteDx9*			texture;
	eSpriteEffect		m_testSpriteEffect;

public:
	DemoState(eIDStateGame ID) : GameState(ID){}
	~DemoState(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif