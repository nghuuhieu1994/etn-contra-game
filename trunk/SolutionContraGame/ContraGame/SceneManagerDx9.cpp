#include "SceneManagerDx9.h"

SceneManagerDx9* SceneManagerDx9::s_Instance = 0;

SceneManagerDx9* SceneManagerDx9::getInstance()
{
	if( !s_Instance )
	{
		s_Instance = new SceneManagerDx9();
	}
	return s_Instance;
}

void SceneManagerDx9::setDirectDevice(const LPDIRECT3DDEVICE9& _lpDirectDevice)
{
	this->m_lpDirectDevice = _lpDirectDevice;
}

void SceneManagerDx9::Initialize()
{
	if( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->InitializeState(m_lpDirectDevice);
	}
}


void SceneManagerDx9::AddElement(GameScene* GameScene)
{
	if(!m_ListGameScene.empty())
	{
		m_ListGameScene[m_ListGameScene.size() - 1]->Pause();
	}
	m_ListGameScene.push_back(GameScene);
	m_ListGameScene.back()->InitializeState(m_lpDirectDevice);
}

void SceneManagerDx9::HandleInput()
{
	if ( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->HandleInput();
	}
}
void SceneManagerDx9::Update()
{
	if ( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->Update();
	}
}
void SceneManagerDx9::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	if ( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->Render(_lpDSpriteHandle);
	}
}
void SceneManagerDx9::ExitState()
{
	if( !m_ListGameScene.empty())
	{
		m_ListGameScene.back()->Release();
		m_ListGameScene.pop_back();
	}
}
void SceneManagerDx9::ReplaceBy(GameScene* GameScene)
{
	ExitState();
	AddElement(GameScene);
}
void SceneManagerDx9::ClearAll()
{
	while( !m_ListGameScene.empty() )
	{
		ExitState();
	}
}

