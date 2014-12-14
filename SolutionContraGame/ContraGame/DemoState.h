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
#include "WeaponSensor.h"
#include "WeaponCapsule.h"
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
#include "WeaponryManager.h"
#include "SnipperWaterHiding.h"
#include "BigStone.h"


#include "MenuGame.h"
#include "Fire.h"
#include "BridgeStone.h"
#include "EnemyBigGunShooting.h"
#include "Tank.h"
#include "FireBridge.h"
#include "BigCapsuleBoss.h"
#include "EnemyRunShooting.h"
#include "Boom.h"
#include "RoShan.h"
#include "WeaponCapsuleVer2.h"
#include "BossPunch.h"
#include "BossArm.h"
//#define HIEU

using namespace std;

class DemoState : public GameScene
{
private:
	Rambo*				m_Rambo;
	QuadTree*			m_Quadtree;
	BackgroundEffect	m_backgroundEffect;
	int					map;
	static int					m_RamboLife;
	static eIDSkillBullet		m_RamboBullet;

	BossPunch*	mPunch;
	BossArm*	mArm[4];
	int countBossArmUpdate;
	D3DXVECTOR3 m_OldPosition;
public:
	DemoState(eIDSceneGame ID, int _map) : GameScene(ID){ map = _map; }
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