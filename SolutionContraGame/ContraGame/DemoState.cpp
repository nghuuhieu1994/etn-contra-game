#include "DemoState.h"
#define MAP_1 1
#define MAP_2 2
#include <fstream>

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	//Punch = new BossPunch(D3DXVECTOR3(100, 100, 1), eDirection::LEFT, eObjectID::ROSHAN_HAND);
	//Punch->Initialize();

	//for (int i = 0; i < 4; i++)
	//{
	//	Arm[i] = new BossArm(D3DXVECTOR3(100, 100, 1), eDirection::LEFT, eObjectID::ROSHAN_HAND);
	//	Arm[i]->Initialize();
	//}

	m_snipperWaterHiding = new SnipperWaterHiding(D3DXVECTOR3(400, 30, 1), eDirection::RIGHT, eObjectID::SNIPPER_WATER_HIDING);
	m_snipperWaterHiding->Initialize();

	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();
	m_Quadtree = new QuadTree();
	fstream fLog("resources\\Map\\" + to_string(map) +"\\setting", ios::in);

	bool lockWidth;
	bool lockHeight;
	D3DXVECTOR2 RamboStartPosition;
	fLog >> lockWidth;
	fLog >> lockHeight;
	fLog >> RamboStartPosition.x;
	fLog >> RamboStartPosition.y;

	m_Rambo = new Rambo(D3DXVECTOR3(RamboStartPosition.x, RamboStartPosition.y, 1), eDirection::RIGHT, eObjectID::RAMBO);
	Camera::getInstance()->Reset();
	Camera::getInstance()->setLockWidth(lockWidth);
	Camera::getInstance()->setLockHeight(lockHeight);

	string mapPath = "resources\\Map\\" + to_string(map) +"\\"+ to_string(map) +".xml";
	m_backgroundEffect.Initialize(map);
	m_Quadtree->BuildQuadtree(mapPath.c_str(), m_Quadtree->mRootNode, (eSpriteID)(map));
	BulletPoolManager::getInstance()->Initialize();
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{
	m_snipperWaterHiding->UpdateAnimation();
	m_snipperWaterHiding->UpdateMovement();
	m_snipperWaterHiding->Update();


	if (m_Rambo->getRamboLife() == 0)
	{
		SceneManagerDx9::getInstance()->ReplaceBy(new MenuGame(eIDSceneGame::INTRO));
	}

	#pragma region Update camera & insert object into quadtree

	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());
	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);

	#pragma endregion

	#pragma region Update rambo

	m_Rambo->UpdateAnimation();
	m_Rambo->SetFlag();
	m_Rambo->UpdateMovement();
	m_Rambo->CleanIgnoreList();

	#pragma endregion

	#pragma region Update Bullet

	BulletPoolManager::getInstance()->Update();
	BulletPoolManager::getInstance()->UpdateMovement();
	BulletPoolManager::getInstance()->UpdateAnimation();

	#pragma endregion

	#pragma region Update Collision for Rambo & Bullet with Object in quadtrere

	#pragma region UPdate Collision for object in quadtree with Bullet

	m_Quadtree->Update();
	m_Quadtree->UpdateAnimation();
	m_Quadtree->UpdateMovement();


	#pragma endregion

	for (int i = 0; i < (int) m_Quadtree->mListObjectCollisionInView.size(); ++i)
	{
		if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getID() == eObjectID::BIG_BOSS_1)
		{
			for (int i = 0; i < (int) m_Quadtree->mListObjectCollisionInView.size(); ++i)
			{
				if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getID() == eObjectID::SNIPER_STANDING)
				{
					(*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).setPositionZ(0.8f);
				}
			}
			//SceneManagerDx9::getInstance()->ReplaceBy(new DemoState(eIDSceneGame::DEMO, 2));
		}
		m_Rambo->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		m_snipperWaterHiding->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		BulletPoolManager::getInstance()->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
	}

	
	for (int i = 0; i < (int) m_Quadtree->mListObjectCollisionInView.size(); ++i)
	{
		m_Quadtree->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);

		WeaponryManager::getInstance()->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);

	}

	for (std::list<Bullet*>::iterator i = BulletPoolManager::getInstance()->m_ListBulletInGame.begin(); i != BulletPoolManager::getInstance()->m_ListBulletInGame.end(); ++i)
	{
		m_Quadtree->UpdateCollision(*i);
		m_Rambo->UpdateCollision(*i);
		m_snipperWaterHiding->UpdateCollision(*i);
	}

	#pragma endregion	

	WeaponryManager::getInstance()->Update();
	WeaponryManager::getInstance()->UpdateCollision(m_Rambo);
	m_Rambo->UpdatePreviousIgnoreList();
	m_backgroundEffect.UpdateAnimation();

	/*Punch->getPhysic()->setVelocityX(0.5f);
	Punch->getPhysic()->setVelocityY(0.5f);
	if (Distance(Punch, Arm[3]) >= 32)
	{
		Arm[3]->getPhysic()->setVelocityX(Punch->getPhysic()->getVelocity().x);
		Arm[3]->getPhysic()->setVelocityY(Punch->getPhysic()->getVelocity().y);
	}
	if (Distance(Arm[3], Arm[2]) > 32)
	{
		Arm[2]->getPhysic()->setVelocityX(Punch->getPhysic()->getVelocity().x);
		Arm[2]->getPhysic()->setVelocityY(Punch->getPhysic()->getVelocity().y);
	}
	if (Distance(Arm[2], Arm[1]) >= 32)
	{
		Arm[1]->getPhysic()->setVelocityX(Punch->getPhysic()->getVelocity().x);
		Arm[1]->getPhysic()->setVelocityY(Punch->getPhysic()->getVelocity().y);
	}

	if (Distance(Arm[1], Arm[0]) >= 32)
	{
		//isPopupDone = true;
		Punch->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
		Punch->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
		for (int i = 0; i < 4; i++)
		{
			Arm[i]->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
			Arm[i]->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
		}
	}



	for (int i = 0; i < 4; i++)
	{
		Arm[i]->UpdateMovement();
	}
	Punch->UpdateMovement();
	*/

}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_Quadtree->Render(_lpDSpriteHandle);
	m_backgroundEffect.Render(_lpDSpriteHandle);
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	WeaponryManager::getInstance()->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	//m_Roshan->Render(_lpDSpriteHandle);
	//m_fireBridge->Render(_lpDSpriteHandle);
	m_snipperWaterHiding->Render(_lpDSpriteHandle);
	//m_boom->Render(_lpDSpriteHandle);
	//m_fireBridge->Render(_lpDSpriteHandle);
	m_snipperWaterHiding->Render(_lpDSpriteHandle);
	//m_boom->Render(_lpDSpriteHandle);
	//m_Tank->Render(_lpDSpriteHandle);
	

	/*for (int i = 0; i < 4; i++)
	{
		Arm[i]->Render(_lpDSpriteHandle);
	}
	Punch->Render(_lpDSpriteHandle);*/
}

void DemoState::Pause()
{

}

void DemoState::Resume()
{

}

void DemoState::Release()
{

}