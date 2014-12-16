#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "GameScene.h"
#include "Rambo.h"
#include "QuadTree.h"
#include "BackgroundEffect.h"
#include "SceneManagerDx9.h"
#include "HighscoreState.h"
#include "MenuGame.h"
#include <fstream>

using namespace std;

class PlayScene :
	public GameScene
{
	int m_mapIndex;
	Rambo*				m_Rambo;
	QuadTree*			m_Quadtree;
	BackgroundEffect	m_backgroundEffect;
	static int m_score;
	static int					m_RamboLife;
	static eIDSkillBullet		m_RamboBullet;
	bool isWin;
	int nextStage;
	float m_timeChangeStage;
	SoundBuffer*		m_SoundBackGround;
public:
	PlayScene(eIDSceneGame ID, int _mapIndex);
	virtual ~PlayScene();
	static void IncreaseScore(){ m_score += 1; }
	static void setScore(int _score){ m_score = _score; }
	void SaveHighScore();
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void ChangeStateBossDie(int _nextStage);
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif