#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_Rambo = new Rambo(D3DXVECTOR3(200, 500, 1), eDirection::RIGHT, eObjectID::RAMBO);
	//SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::THEME_SONG_S_1)->Repeat();
	
	m_Quadtree = new QuadTree();

	string mapPath = "resources\\Map\\" + to_string(1) +"\\"+ to_string(1) +".xml";
	m_led.Initialize(1);
	m_Quadtree->BuildQuadtree(mapPath.c_str(), m_Quadtree->mRootNode, (eSpriteID)(1));

	BulletPoolManager::getInstance()->Initialize();

	m_tile = new Bridge(D3DXVECTOR3(1664, 224, 1), eDirection::LEFT, eObjectID::BRIDGE);
	m_tile->Initialize();
	
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

	for(std::list<Bullet*>::iterator i = BulletPoolManager::getInstance()->m_ListBulletInGame.begin(); i != BulletPoolManager::getInstance()->m_ListBulletInGame.end(); ++i)
	{
		m_Quadtree->UpdateCollision(*i);
	}

	#pragma endregion

	for(int i = 0; i < m_Quadtree->mListObjectCollisionInView.size(); ++i)
	{
		m_Rambo->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
		//BulletPoolManager::getInstance()->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
	}

	#pragma endregion

	m_Rambo->UpdatePreviousIgnoreList();
	
	m_Quadtree->UpdateAnimation();
	m_Quadtree->Update();
	
	m_led.UpdateAnimation();
	m_tile->UpdateAnimation();
	m_tile->Update();

}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_Quadtree->Render(_lpDSpriteHandle);
	m_led.Render(_lpDSpriteHandle);	
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
	m_tile->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
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