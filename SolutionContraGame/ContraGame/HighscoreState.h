#ifndef _HIGH_SCORE_H__
#define _HIGH_SCORE_H__

//#include "CSpriteDx9.h"
#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"

class HighScoreState : public GameScene
{
private:
	bool m_IsDone;
	LPD3DXFONT m_Font;
	CSpriteDx9*			m_MenuBG;
	int NextStage;
	float coolDonwChange;
public:
	HighScoreState(eIDSceneGame ID, int nextStage) : GameScene(ID) { NextStage = nextStage; }
	~HighScoreState(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};


#endif