#include "DemoState.h"
#define MAP_1 1
#define MAP_2 2

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	/*
	m_MagicRock = new MagicRock(D3DXVECTOR3( 200, 30, 1), eDirection::RIGHT, eObjectID::MAGIC_ROCK);
	m_MagicRock->Initialize();
	m_SnipperWaterHiding = new SnipperWaterHiding(D3DXVECTOR3( 350, 70, 1), eDirection::RIGHT, eObjectID::SNIPPER_WATER_HIDING);
	m_SnipperWaterHiding->Initialize();
	m_Stone = new Stone(D3DXVECTOR3( 400, 300, 1), eDirection::RIGHT, eObjectID::STONE);
	m_Stone->Initialize();
	m_Fire = new Fire(D3DXVECTOR3(300, 50, 1), eDirection::RIGHT, eObjectID::FIRE);
	m_Fire->Initialize();
	m_MagicStone = new MagicStone(D3DXVECTOR3(200, 200, 1), eDirection::RIGHT, eObjectID::MAGIC_ROCK);
	m_MagicStone->Initialize();

	m_Rambo = new Rambo(D3DXVECTOR3(200, 500, 1), eDirection::RIGHT, eObjectID::RAMBO);
	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();
	m_Quadtree = new QuadTree();
	//Camera::getInstance()->setLockWidth(true);
	Camera::getInstance()->setLockHeight(true);
	string mapPath = "resources\\Map\\" + to_string(MAP_1) +"\\"+ to_string(MAP_1) +".xml";
	m_backgroundEffect.Initialize(MAP_1);
	m_Quadtree->BuildQuadtree(mapPath.c_str(), m_Quadtree->mRootNode, (eSpriteID)(MAP_1));
	BulletPoolManager::getInstance()->Initialize();

<<<<<<< .mine
	m_Tinker = new Tinker(D3DXVECTOR3(200, 300, 1), eDirection::LEFT, eObjectID::BIG_BOSS_1);
	m_Tinker->Initialize();*/
	m_capsuleBoss = new BigCapsuleBoss(D3DXVECTOR3(300, 300, 1), eDirection::RIGHT, eObjectID::BIG_CAPSULE_BOSS);
	m_capsuleBoss->Initialize();
}


void DemoState::HandleInput()
{
	//m_Rambo->HandleInput();
}

void DemoState::Update()
{
	
	/*#pragma region Update camera & insert object into quadtree

	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());
	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);

	#pragma endregion
	//m_SnipperWaterHiding->UpdateAnimation();
	//m_SnipperWaterHiding->Update();

	m_Stone->UpdateAnimation();
	m_Stone->Update();
	m_Stone->UpdateMovement();

	m_Fire->UpdateAnimation();
	m_Fire->UpdateMovement();

	m_MagicStone->UpdateAnimation();
	m_MagicStone->UpdateMovement();


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

	for(int i = 0; i < (int)m_Quadtree->mListObjectCollisionInView.size(); ++i)
	{
		m_Rambo->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		m_Stone->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		BulletPoolManager::getInstance()->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
	}

	
	for(int i = 0; i < (int)m_Quadtree->mListObjectCollisionInView.size(); ++i)
	{
		m_Quadtree->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);

		WeaponryManager::getInstance()->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
	}

	for(std::list<Bullet*>::iterator i = BulletPoolManager::getInstance()->m_ListBulletInGame.begin(); i != BulletPoolManager::getInstance()->m_ListBulletInGame.end(); ++i)
	{
		m_Quadtree->UpdateCollision(*i);
		m_Rambo->UpdateCollision(*i);
		m_Stone->UpdateCollision(*i);
		m_SnipperWaterHiding->UpdateCollision(*i);
		//m_Tinker->UpdateCollision(*i);
	}

	#pragma endregion	

	WeaponryManager::getInstance()->Update();
	WeaponryManager::getInstance()->UpdateCollision(m_Rambo);
	m_Rambo->UpdatePreviousIgnoreList();
	m_backgroundEffect.UpdateAnimation();
	
<<<<<<< .mine
<<<<<<< .mine
	m_Tinker->UpdateAnimation();
	m_Tinker->Update();*/

	m_capsuleBoss->Update();
	m_capsuleBoss->UpdateAnimation();
	m_capsuleBoss->UpdateMovement();
	m_capsuleBoss->UpdateCollision(NULL);
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	///*m_Quadtree->Render(_lpDSpriteHandle);
	//m_backgroundEffect.Render(_lpDSpriteHandle);*/
	//BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	//WeaponryManager::getInstance()->Render(_lpDSpriteHandle);
	////m_Rambo->Render(_lpDSpriteHandle);
	//m_Tinker->Render(_lpDSpriteHandle);
	////m_MagicRock->Render(_lpDSpriteHandle);
	m_capsuleBoss->Render(_lpDSpriteHandle);
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