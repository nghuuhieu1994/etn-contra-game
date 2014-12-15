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


	//rs = new Roshan(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1), eDirection::RIGHT, eObjectID::ROSHAN);
	//rs->Initialize();
}

void DemoState::HandleInput()
{
	string scriptPath = "resources\\Map\\" + to_string(map) +"\\autorun";
	m_Rambo->RunScript(scriptPath.c_str());
	m_Rambo->HandleInput();
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

}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_Quadtree->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	m_backgroundEffect.Render(_lpDSpriteHandle);
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	WeaponryManager::getInstance()->Render(_lpDSpriteHandle);
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