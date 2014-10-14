#ifndef __TEST_SPRITE_STATE_H__
#define __TEST_SPRITE_STATE_H__
#include "GameState.h"
#include "StateManagerDx9.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"

#define CENTERX 400
#define CENTERY 300

class TestSpriteState : public GameState
{
private:
	CSpriteDx9* testSprite;
public:
	TestSpriteState(eIDStateGame ID) : GameState(ID){}
	~TestSpriteState(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif