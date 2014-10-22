#ifndef __TEST_SPRITE_STATE_H__
#define __TEST_SPRITE_STATE_H__

#include "CSpriteDx9.h"
#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"

#define CENTERX 400
#define CENTERY 300

class TestSpriteState : public GameScene
{
private:
	CSpriteDx9* testSprite;
public:
	TestSpriteState(eIDSceneGame ID) : GameScene(ID){}
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