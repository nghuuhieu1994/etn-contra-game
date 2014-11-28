#ifndef __DEMO_STATE_H__
#define __DEMO_STATE_H__

#include "GameScene.h"
#include "SceneManagerDx9.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"
#include "CCamera.h"
#include "SoundMangerDx9.h"
#include "MapReader.h"
#include "Rambo.h"
#include "SniperStanding.h"
#include "GifBulletStatic.h"
#include "GifBulletMoving.h"
#include "GunRotating.h"
#include "BigGunRotating.h"
#include "Tile.h"
#include "EnemyRun.h"
#include "Markup.h"
#include "VirtualObject.h"
#include "SniperHiding.h"
#include "BossGun.h"
#include "BossCenter.h"
#include "Bullet.h"
#include "Tinker.h"
#include "BulletPoolManager.h"
#include "BulletPool.h"
#include "BackgroundEffect.h"
#include <list>
#include "QuadTree.h"
#include "Bridge.h"
//#define HIEU

using namespace std;

class DemoState : public GameScene
{
private:
	Rambo*				m_Rambo;
	QuadTree*			m_Quadtree;
	BackgroundEffect	m_led;
	Bridge*				m_tile;
public:
	DemoState(eIDSceneGame ID) : GameScene(ID){}
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