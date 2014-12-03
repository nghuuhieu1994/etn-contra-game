#include "DemoState.h"
#define MAP_1 1
#define MAP_2 2

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_MagicRock = new MagicRock(D3DXVECTOR3( 200, 30, 1), eDirection::RIGHT, eObjectID::MAGIC_ROCK);
	m_MagicRock->Initialize();
	m_Rambo = new Rambo(D3DXVECTOR3(200, 500, 1), eDirection::RIGHT, eObjectID::RAMBO);
	SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();
	m_Quadtree = new QuadTree();
	//Camera::getInstance()->setLockWidth(true);
	Camera::getInstance()->setLockHeight(true);
	string mapPath = "resources\\Map\\" + to_string(MAP_1) +"\\"+ to_string(MAP_1) +".xml";
	m_backgroundEffect.Initialize(MAP_1);
	m_Quadtree->BuildQuadtree(mapPath.c_str(), m_Quadtree->mRootNode, (eSpriteID)(MAP_1));
	BulletPoolManager::getInstance()->Initialize();
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{
	#pragma region Update camera & insert object into quadtree

	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());
	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);

	#pragma endregion
	m_MagicRock->UpdateAnimation();
	m_MagicRock->UpdateMovement();
	m_MagicRock->Update();

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
	m_backgroundEffect.Render(_lpDSpriteHandle);	
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	WeaponryManager::getInstance()->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	m_MagicRock->Render(_lpDSpriteHandle);
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