#include "DemoState.h"


void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	
	m_Rambo = new Rambo(D3DXVECTOR3(200, 600, 1), eDirection::RIGHT, eObjectID::RAMBO);

	m_myTinker = new Tinker(D3DXVECTOR3(200, 200, 1), eDirection::LEFT, eObjectID::BIG_BOSS_1);
	m_myTinker->Initialize();

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
	m_Quadtree->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Quadtree->mRootNode);

	m_Rambo->Update();
	m_Rambo->UpdateAnimation();
	m_Rambo->UpdateMovement();
	
	//for(std::list<Object*>::iterator i = m_Quadtree->mListObjectInView.begin(); i != m_Quadtree->mListObjectInView.end(); ++i)
	//{
	//	if((*i)->getTypeObject() == ETypeObject::VIRTUAL_OBJECT)
	//	{
	//		m_Rambo->UpdateCollision((*i));
	//	}
	//}

	for(int i = 0; i < (int)m_Quadtree->mListObjectInView.size(); ++i)
	{
		if(m_Quadtree->mListObjectInView[i]->getTypeObject() == ETypeObject::VIRTUAL_OBJECT)
		{
			m_Rambo->UpdateCollision(m_Quadtree->mListObjectInView[i]);
		}
	}
	m_Rambo->Update(m_Quadtree->mListObjectInView);

	m_myTinker->UpdateAnimation();

}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	for(int i = 0; i < (int)m_Quadtree->mListObjectInView.size(); ++i)
	{
		m_Quadtree->mListObjectInView[i]->Render(_lpDSpriteHandle);
	}

	m_Rambo->Render(_lpDSpriteHandle);
	BulletPoolManager::getInstance()->Render(_lpDSpriteHandle);

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