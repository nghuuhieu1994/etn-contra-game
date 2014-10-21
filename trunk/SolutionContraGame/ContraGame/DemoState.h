#ifndef __DEMO_STATE_H__
#define __DEMO_STATE_H__

#include "GameState.h"
#include "StateManagerDx9.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"
#include "CCamera.h"
#include "SoundMangerDx9.h"
#include "Background.h"
#include "Rambo.h"
#include "SniperStanding.h"
#include "GifBulletStatic.h"
#include "GifBulletMoving.h"
#include "GunRotating.h"
#include "Tile.h"
#include "EnemyRun.h"
#include "Markup.h"
#include "VirtualObject.h"
#include <list>

using namespace std;

class DemoState : public GameState
{
private:
	D3DXVECTOR3			m_UnitTest;
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
	SniperStanding*		m_SniperStanding;
	GifBulletStatic*	m_gifBullet;
	GifBulletMoving*	m_gifBulletMoving;
	GunRotating*		m_gunRotating;
	EnemyRun*			m_Enemy;
	VirtualObject*		m_VirtualObject;

	list<Object *> _ListGameObjects;

public:
	DemoState(eIDStateGame ID) : GameState(ID){}
	~DemoState(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void ReadMap();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif