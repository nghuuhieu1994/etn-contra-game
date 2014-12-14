#ifndef __WIN_GAME_H__
#define __WIN_GAME_H__

//#include "CSpriteDx9.h"
#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"

class WinGameScene : public GameScene
{
private:
	CSpriteDx9*			m_WinSceneBG;
	D3DXVECTOR3			m_WinScenePosition;
	bool m_isDone;
public:
	WinGameScene(eIDSceneGame ID) : GameScene(ID) {}
	~WinGameScene(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};


#endif