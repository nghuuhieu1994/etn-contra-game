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
	
	static int					m_RamboLife;
	static eIDSkillBullet		m_RamboBullet;
public:
	PlayScene(eIDSceneGame ID, int _mapIndex);
	virtual ~PlayScene();
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif