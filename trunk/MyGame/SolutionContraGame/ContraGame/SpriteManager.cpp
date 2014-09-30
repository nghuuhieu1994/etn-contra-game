#include "SpriteManager.h"

SpriteManager* SpriteManager::s_Instance = 0;

SpriteManager::SpriteManager(void)
{
	
}

SpriteManager* SpriteManager::GetInstance()
{
	if(s_Instance == 0)
	{
		s_Instance = new SpriteManager();
	}
	return s_Instance;
}

void SpriteManager::LoadSpriteContent(LPDIRECT3DDEVICE9 _lpDirectDevice, const char* fileName, eSpriteID SpriteID, int Column, int Row, int TotalFrame)
{
	CSpriteDx9* sprite = new CSpriteDx9();
	sprite->LoadContent(_lpDirectDevice, fileName, Column, Row, TotalFrame);
	m_ListSprite[SpriteID] = sprite;
}

CSpriteDx9* SpriteManager::GetSoundBuffer(eSpriteID eID)
{
	map<eSpriteID, CSpriteDx9*>::iterator i;
	i = m_ListSprite.find(eID);
	if(i == m_ListSprite.end())
		return NULL;
	return i->second;
}

void SpriteManager::InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_jump.png", eSpriteID::BILL_JUMP, 4, 1, 4);
	m_ListSprite[eSpriteID::BILL_JUMP]->m_AnimationAction->setIndexStart(0);
	m_ListSprite[eSpriteID::BILL_JUMP]->m_AnimationAction->setIndexEnd(3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_lie.png", eSpriteID::BILL_LIE_DOWN, 1, 1, 1);
}

SpriteManager::~SpriteManager(void)
{
}
