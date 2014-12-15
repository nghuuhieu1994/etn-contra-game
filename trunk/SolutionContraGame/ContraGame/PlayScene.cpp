#include "PlayScene.h"
int PlayScene::m_RamboLife = 10;
int PlayScene::m_score = 0;
eIDSkillBullet PlayScene::m_RamboBullet = eIDSkillBullet::DEFAULT_SKILL_BULLET;

PlayScene::PlayScene(eIDSceneGame ID, int _mapIndex) : GameScene(ID)
{
	m_mapIndex = _mapIndex;
}

void PlayScene::SaveHighScore()
{
	fstream fLog("resources\\Map\\MenuGame\\highscore", ios::in | ios::out | ios::app);
	int oldHighScore;
	fLog >> oldHighScore;
	fLog.close();
	if (m_score > oldHighScore)
	{
		fstream fLog("resources\\Map\\MenuGame\\highscore", ios::out | ios::trunc);
		fLog << m_score;
	}
}

void PlayScene::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_Quadtree = new QuadTree();
	fstream fLog("resources\\Map\\" + to_string(m_mapIndex) +"\\setting", ios::in);

	bool lockWidth;
	bool lockHeight;
	D3DXVECTOR2 RamboStartPosition;
	fLog >> lockWidth;
	fLog >> lockHeight;
	fLog >> RamboStartPosition.x;
	fLog >> RamboStartPosition.y;
	m_Rambo = new Rambo(D3DXVECTOR3(RamboStartPosition.x, RamboStartPosition.y, 1), eDirection::RIGHT, eObjectID::RAMBO);

	string cameraPath = "resources\\Map\\" + to_string(m_mapIndex) +"\\camera";
	Camera::getInstance()->Reset();
	Camera::getInstance()->readAutoRunScript(cameraPath.c_str());
	Camera::getInstance()->setLockWidth(lockWidth);
	Camera::getInstance()->setLockHeight(lockHeight);

	string mapPath = "resources\\Map\\" + to_string(m_mapIndex) +"\\"+ to_string(m_mapIndex) +".xml";
	m_backgroundEffect.Initialize(m_mapIndex);
	m_Quadtree->BuildQuadtree(mapPath.c_str(), m_Quadtree->mRootNode, (eSpriteID)(m_mapIndex));
	BulletPoolManager::getInstance()->Initialize();
	m_Rambo->setRamboLife(PlayScene::m_RamboLife);
	m_Rambo->setSkillBullet(PlayScene::m_RamboBullet);
}

void PlayScene::HandleInput()
{
	m_Rambo->HandleInput();
}

void PlayScene::Update()
{
	if (m_Rambo->getRamboLife() == 0)
	{
		SceneManagerDx9::getInstance()->ReplaceBy(new HighScoreState(eIDSceneGame::INTRO, 0));
		SaveHighScore();
	}

	#pragma region Update camera & insert object into quadtree

	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());
	if (!Camera::getInstance()->IsGamePause())
	{
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
					PlayScene::m_RamboBullet = m_Rambo->getSkillBullet();
					PlayScene::m_RamboLife = m_Rambo->getRamboLife();
					SceneManagerDx9::getInstance()->ReplaceBy(new HighScoreState(eIDSceneGame::DEMO, 2));
					SaveHighScore();
				}
			}
			if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getID() == eObjectID::ROSHAN)
			{
				if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getObjectState() == eObjectState::STATE_BOSS_DEATH)
				{
					PlayScene::m_RamboBullet = m_Rambo->getSkillBullet();
					PlayScene::m_RamboLife = m_Rambo->getRamboLife();
					SceneManagerDx9::getInstance()->ReplaceBy(new HighScoreState(eIDSceneGame::DEMO, 3));
					SaveHighScore();
				}
			}
			if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getID() == eObjectID::BIG_CAPSULE_BOSS)
			{
				if ((*m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]).getObjectState() == eObjectState::STATE_BOSS_DEATH)
				{
					PlayScene::m_RamboBullet = m_Rambo->getSkillBullet();
					PlayScene::m_RamboLife = m_Rambo->getRamboLife();
					SceneManagerDx9::getInstance()->ReplaceBy(new HighScoreState(eIDSceneGame::DEMO, -1));
					SaveHighScore();
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
}

void PlayScene::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_Quadtree->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	m_backgroundEffect.Render(_lpDSpriteHandle);
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	WeaponryManager::getInstance()->Render(_lpDSpriteHandle);
}

void PlayScene::Pause()
{

}

void PlayScene::Resume()
{

}

void PlayScene::Release()
{
	m_Quadtree->Release(m_Quadtree->getRootNode());
}

PlayScene::~PlayScene()
{
}
