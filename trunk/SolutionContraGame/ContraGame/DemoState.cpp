#include "DemoState.h"
#include "HighScoreState.h"
#define MAP_1 1
#define MAP_2 2
#include <fstream>
int DemoState::m_RamboLife = 10;
eIDSkillBullet DemoState::m_RamboBullet = eIDSkillBullet::DEFAULT_SKILL_BULLET;

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{


	m_Quadtree = new QuadTree();
	fstream fLog("resources\\Map\\" + to_string(map) +"\\setting", ios::in);

	bool lockWidth;
	bool lockHeight;
	D3DXVECTOR2 RamboStartPosition;
	fLog >> lockWidth;
	fLog >> lockHeight;
	fLog >> RamboStartPosition.x;
	fLog >> RamboStartPosition.y;

	//m_Rambo = new Rambo(D3DXVECTOR3(50, RamboStartPosition.y, 1), eDirection::RIGHT, eObjectID::RAMBO);
	m_Rambo = new Rambo(D3DXVECTOR3(RamboStartPosition.x, RamboStartPosition.y, 1), eDirection::RIGHT, eObjectID::RAMBO);
	string cameraPath = "resources\\Map\\" + to_string(map) +"\\camera";
	Camera::getInstance()->Reset();
	Camera::getInstance()->readAutoRunScript(cameraPath.c_str());
	Camera::getInstance()->setLockWidth(lockWidth);
	Camera::getInstance()->setLockHeight(lockHeight);

	string mapPath = "resources\\Map\\" + to_string(map) +"\\"+ to_string(map) +".xml";
	m_backgroundEffect.Initialize(map);
	m_Quadtree->BuildQuadtree(mapPath.c_str(), m_Quadtree->mRootNode, (eSpriteID)(map));
	BulletPoolManager::getInstance()->Initialize();
	m_Rambo->setRamboLife(DemoState::m_RamboLife);
	m_Rambo->setSkillBullet(DemoState::m_RamboBullet);

	m_BossHand = new BossHand(D3DXVECTOR3(300, 300, 1.0f), eDirection::LEFT, eObjectID::ROSHAN_HAND);
	m_BossHand->Initialize();

	//mPunch = new BossPunch(D3DXVECTOR3(100, 100, 1), eDirection::RIGHT, eObjectID::ROSHAN_PUNCH);
	//mPunch->Initialize();
	//for (int i = 0; i < 4; i++)
	//{
	countBossArmUpdate = 0;
	mArm[0] = new BossArm(D3DXVECTOR3(100, 100, 1), eDirection::RIGHT, eObjectID::ROSHAN_ARM, D3DXVECTOR3(100, 100, 1), 0.0f);
	mArm[0]->Initialize();
	mArm[0]->setAngleVeclocity(0.00f);
	//mArm[0]->setAngle(0.0f);
	mArm[1] = new BossArm(D3DXVECTOR3(100 + 32, 100 + 16, 1), eDirection::RIGHT, eObjectID::ROSHAN_ARM, D3DXVECTOR3(100, 100, 1), 0.1f);
	mArm[1]->Initialize();
	mArm[1]->setFactorR(32);
	mArm[1]->setAngleVeclocity(4);
	//mArm[1]->setIsRootNode(true);
	mArm[1]->setAngle(0);
	mArm[2] = new BossArm(D3DXVECTOR3(100 + 64, 100 + 32, 1), eDirection::RIGHT, eObjectID::ROSHAN_ARM, D3DXVECTOR3(100 + 32, 100 + 16, 1), 0.11f);
	mArm[2]->Initialize();
	mArm[2]->setFactorR(64);
	mArm[2]->setAngleVeclocity(-60);
	mArm[3] = new BossArm(D3DXVECTOR3(100 + 96, 100 + 48, 1), eDirection::RIGHT, eObjectID::ROSHAN_ARM, D3DXVECTOR3(100 + 64, 100 + 32, 1), 0.12f);
	mArm[3]->Initialize();
	mArm[3]->setFactorR(96);
	mArm[3]->setAngleVeclocity(-50);
	//}

	//rs = new Roshan(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1), eDirection::RIGHT, eObjectID::ROSHAN);
	//rs->Initialize();
}

void DemoState::HandleInput()
{
	string scriptPath = "resources\\Map\\" + to_string(map) +"\\autorun";
	m_Rambo->RunScript(scriptPath.c_str());
}

void DemoState::Update()
{
	if (m_Rambo->getRamboLife() == 0)
	{
		SceneManagerDx9::getInstance()->ReplaceBy(new MenuGame(eIDSceneGame::INTRO));
	}

	#pragma region Update camera & insert object into quadtree

	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());
	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);

	#pragma endregion

	#pragma region Update rambo

	//m_Rambo->HandleInput();
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
					(*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).setPositionZ(1.0f);
				}
			}
			//SceneManagerDx9::getInstance()->ReplaceBy(new DemoState(eIDSceneGame::DEMO, 2));
		}
		if((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getID() == eObjectID::WEAPON_CAPSULE)
		{
			WeaponCapsule* temp = (WeaponCapsule*)m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]];
			if(temp->m_IsUpdated == false)
			{
				(*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).setPositionX(m_Rambo->getPositionVec2().x - 200);
				temp->m_IsUpdated = true;
			}
		}

		m_Rambo->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		BulletPoolManager::getInstance()->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getID() == eObjectID::BIG_BOSS_1)
		{
			if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getObjectState() == eObjectState::STATE_BOSS_DEATH)
			{
				DemoState::m_RamboBullet = m_Rambo->getSkillBullet();
				DemoState::m_RamboLife = m_Rambo->getRamboLife();
				SceneManagerDx9::getInstance()->ReplaceBy(new HighScoreState(eIDSceneGame::DEMO, 2)); 
			}
		}
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
	}

	#pragma endregion	

	WeaponryManager::getInstance()->Update();
	WeaponryManager::getInstance()->UpdateCollision(m_Rambo);
	m_Rambo->UpdatePreviousIgnoreList();
	m_backgroundEffect.UpdateAnimation();
	

	// Popup action
	//mPunch->getPhysic()->setVelocityX(0.3f); // VELOC_POPUP_X
	//mPunch->getPhysic()->setVelocityY(0.4f); // VELOC_POPUP_Y

	//if (Distance(mPunch, mArm[3]) >= 32)
	//{
	//	mArm[3]->getPhysic()->setVelocityX(mPunch->getPhysic()->getVelocity().x);
	//	mArm[3]->getPhysic()->setVelocityY(mPunch->getPhysic()->getVelocity().y);
	//}
	//if (Distance(mArm[3], mArm[2]) > 32)
	//{
	//	mArm[2]->getPhysic()->setVelocityX(mPunch->getPhysic()->getVelocity().x);
	//	mArm[2]->getPhysic()->setVelocityY(mPunch->getPhysic()->getVelocity().y);
	//}
	//if (Distance(mArm[2], mArm[1]) >= 32)
	//{
	//	mArm[1]->getPhysic()->setVelocityX(mPunch->getPhysic()->getVelocity().x);
	//	mArm[1]->getPhysic()->setVelocityY(mPunch->getPhysic()->getVelocity().y);
	//}

	//if (Distance(mArm[1], mArm[0]) >= 32)
	//{
	//	//isPopupDone = true;
	//	mPunch->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
	//	mPunch->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
	//	for (int i = 0; i < 4; i++)
	//	{
	//		mArm[i]->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
	//		mArm[i]->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
	//	}
	//}

	//for (int i = 1; i < 4; i++)
	//{
	//	if(i > 1)
	//	{
	//		mArm[i]->setPositionOfOring(mArm[i-1]->getPositionVec3());
	//		mArm[i]->setAngle(mArm[i-1]->getAngle());
	//	}	
	//	mArm[i]->UpdateMovement();
	//}

	m_BossHand->UpdateMovement();

	//mPunch->UpdateMovement();

	//rs->Update();
	//rs->UpdateAnimation();
	//rs->UpdateMovement();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	//m_Quadtree->Render(_lpDSpriteHandle);
	//m_Rambo->Render(_lpDSpriteHandle);
	//m_backgroundEffect.Render(_lpDSpriteHandle);
	//BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	//WeaponryManager::getInstance()->Render(_lpDSpriteHandle);

	//for (int i = 0; i < 4; i++)
	//{
	//	mArm[i]->Render(_lpDSpriteHandle);
	//}

	//mArm[0]->Render(_lpDSpriteHandle);
	//mArm[1]->Render(_lpDSpriteHandle);
	//mArm[2]->Render(_lpDSpriteHandle);

	//mPunch->Render(_lpDSpriteHandle);

	m_BossHand->Render(_lpDSpriteHandle);
	//rs->Render(_lpDSpriteHandle);
}

void DemoState::Pause()
{

}

void DemoState::Resume()
{

}

void DemoState::Release()
{
	//m_Quadtree->Release(m_Quadtree->getRootNode());
}