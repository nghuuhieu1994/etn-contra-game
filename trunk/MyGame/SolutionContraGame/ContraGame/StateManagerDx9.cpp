#include "StateManagerDx9.h"

StateManagerDx9* StateManagerDx9::s_Instance = NULL;

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
	if( !ListGameState.empty() )
	{
		ListGameState.back()->InitializeState(m_lpDirectDevice);
	}
}


void StateManagerDx9::AddElement(GameState* gameState)
{
	if(!ListGameState.empty())
	{
		ListGameState[ListGameState.size() - 1]->Pause();
	}
	ListGameState.push_back(gameState);
	ListGameState.back()->InitializeState(m_lpDirectDevice);
}

void StateManagerDx9::UpdateHanleInput()
{
	if ( !ListGameState.empty() )
	{
		ListGameState.back()->UpdateHandleInput();
	}
}
void StateManagerDx9::Update()
{
	if ( !ListGameState.empty() )
	{
		ListGameState.back()->Update();
	}
}
void StateManagerDx9::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	if ( !ListGameState.empty() )
	{
		ListGameState.back()->Render(_lpDSpriteHandle);
	}
}
void StateManagerDx9::ExitState()
{
	if( !ListGameState.empty())
	{
		ListGameState.back()->Release();
		ListGameState.pop_back();
	}
}
void StateManagerDx9::ReplaceBy(GameState* gameState)
{
	ExitState();
	AddElement(gameState);
}
void StateManagerDx9::ClearAll()
{
	while( !ListGameState.empty() )
	{
		ExitState();
	}
}

