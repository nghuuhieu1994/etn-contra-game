#include "StateManagerDx9.h"

StateManagerDx9* StateManagerDx9::s_Instance = 0;

StateManagerDx9* StateManagerDx9::getInstance()
{
	if( !s_Instance )
	{
		s_Instance = new StateManagerDx9();
	}
	return s_Instance;
}

void StateManagerDx9::setDirectDevice(const LPDIRECT3DDEVICE9& _lpDirectDevice)
{
	this->m_lpDirectDevice = _lpDirectDevice;
}

void StateManagerDx9::Initialize()
{
	if( !m_ListGameState.empty() )
	{
		m_ListGameState.back()->InitializeState(m_lpDirectDevice);
	}
}


void StateManagerDx9::AddElement(GameState* gameState)
{
	if(!m_ListGameState.empty())
	{
		m_ListGameState[m_ListGameState.size() - 1]->Pause();
	}
	m_ListGameState.push_back(gameState);
	m_ListGameState.back()->InitializeState(m_lpDirectDevice);
}

void StateManagerDx9::HandleInput()
{
	if ( !m_ListGameState.empty() )
	{
		m_ListGameState.back()->HandleInput();
	}
}
void StateManagerDx9::Update()
{
	if ( !m_ListGameState.empty() )
	{
		m_ListGameState.back()->Update();
	}
}
void StateManagerDx9::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	if ( !m_ListGameState.empty() )
	{
		m_ListGameState.back()->Render(_lpDSpriteHandle);
	}
}
void StateManagerDx9::ExitState()
{
	if( !m_ListGameState.empty())
	{
		m_ListGameState.back()->Release();
		m_ListGameState.pop_back();
	}
}
void StateManagerDx9::ReplaceBy(GameState* gameState)
{
	ExitState();
	AddElement(gameState);
}
void StateManagerDx9::ClearAll()
{
	while( !m_ListGameState.empty() )
	{
		ExitState();
	}
}

