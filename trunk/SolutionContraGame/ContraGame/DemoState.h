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
#include "BulletPoolManager.h"
#include "BulletPool.h"
#include "LedObject.h"
#include <list>

//#define HIEU

using namespace std;

class DemoState : public GameScene
{
private:
	//D3DXVECTOR3			m_UnitTest;
	/*CSpriteDx9*			texture;
	CSpriteDx9*			billmove1;
	CSpriteDx9*			billmove2;
	CSpriteDx9*			billmove3;
	CSpriteDx9*			billmove4;
	CSpriteDx9*			billmove5[3];
	CSpriteDx9*			billjump;
	CSpriteDx9*			fBullet;
	CSpriteDx9*			backGround;
	ESpriteEffect		m_testSpriteEffect;*/
//	Background*			m_background;
	Rambo*				m_Rambo;


#ifdef HIEU
	SniperStanding*		m_SniperStanding;
	GifBulletStatic*	m_gifBullet;
	GifBulletMoving*	m_gifBulletMoving;
	GunRotating*		m_gunRotating;
	EnemyRun*			m_Enemy;
	BigGunRotating*		m_bigGunRotating;
	SniperHiding*		m_snipperHiding;
	BossGun*			m_bossGun;
	BossCenter*			m_bossCenter;  
#endif // HIEU

	EnemyRun*			m_Enemy;

	list<Object *>		m_listGameObjects;

	list<Object *>		m_backgroundTile;

	list<Object *>		m_ledObject;
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