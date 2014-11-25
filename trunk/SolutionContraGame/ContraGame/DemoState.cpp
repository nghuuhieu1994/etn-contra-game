#include "DemoState.h"


void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_Rambo = new Rambo(D3DXVECTOR3(200, 600, 1), eDirection::RIGHT, eObjectID::RAMBO);

	

	m_Quadtree = new QuadTree();
	m_Quadtree->BuildQuadtree("resources\\Map\\1\\map.xml", m_Quadtree->mRootNode);
	BulletPoolManager::getInstance()->Initialize();
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{
	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());
	
	BulletPoolManager::getInstance()->Update();
	BulletPoolManager::getInstance()->UpdateMovement();
	BulletPoolManager::getInstance()->UpdateAnimation();

	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);

	m_Rambo->UpdateAnimation();
	m_Rambo->SetFlag();
	
	m_Rambo->UpdateMovement();
	m_Rambo->CleanIgnoreList();

	for(int i = 0; i < m_Quadtree->mListObjectCollisionInView.size(); ++i)
	{
		m_Rambo->UpdateCollision(m_Quadtree->mMapObjectCollisionInGame[m_Quadtree->mListObjectCollisionInView[i]]);
	}

	m_Rambo->UpdatePreviousIgnoreList();
	
	for(std::list<Bullet*>::iterator i = BulletPoolManager::getInstance()->m_ListBulletInGame.begin(); i != BulletPoolManager::getInstance()->m_ListBulletInGame.end(); ++i)
	{
		m_Quadtree->UpdateCollision(*i);
	}
	
	m_Quadtree->UpdateAnimation();
	m_Quadtree->Update();
	
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_Quadtree->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);
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