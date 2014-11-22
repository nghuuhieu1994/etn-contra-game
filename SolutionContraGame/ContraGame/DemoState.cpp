#include "DemoState.h"


void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_Rambo = new Rambo(D3DXVECTOR3(200, 600, 1), eDirection::RIGHT, eObjectID::RAMBO);

	m_myTinker = new Tinker(D3DXVECTOR3(200, 200, 1), eDirection::LEFT, eObjectID::BIG_BOSS_1);
	m_myTinker->Initialize();

	m_Quadtree = new QuadTree();
	m_Quadtree->BuildQuadtree("resources\\Map\\1\\map.xml", m_Quadtree->mRootNode);
	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);
	BulletPoolManager::getInstance()->Initialize();
}

void DemoState::HandleInput()
{
}

void DemoState::Update()
{
	m_myTinker->UpdateAnimation();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_myTinker->Render(_lpDSpriteHandle);
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