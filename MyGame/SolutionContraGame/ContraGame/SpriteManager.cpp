#include "SpriteManager.h"

SpriteManager* SpriteManager::s_Instance = 0;

SpriteManager::SpriteManager(void)
{
	
}

SpriteManager* SpriteManager::getInstance()
{
	if(s_Instance == 0)
	{
		s_Instance = new SpriteManager();
	}
	return s_Instance;
}

void SpriteManager::LoadSpriteContent(LPDIRECT3DDEVICE9 _lpDirectDevice, const char* fileName, eSpriteID eID, int Column, int Row, int TotalFrame)
{
	CSpriteDx9* sprite = new CSpriteDx9();
	sprite->LoadContent(_lpDirectDevice, fileName, Column, Row, TotalFrame);
	m_ListSprite[eID] = sprite;
}

CSpriteDx9* SpriteManager::GetSprite(eSpriteID eID)
{
	map<eSpriteID, CSpriteDx9*>::iterator i;

	i = m_ListSprite.find(eID);

	if(i == m_ListSprite.end())
		return 0;

	return i->second;
}

void SpriteManager::InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_jump.png", eSpriteID::BILL_JUMP, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_lie.png", eSpriteID::BILL_LIE_DOWN, 1, 1, 1);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_1.png", eSpriteID::BILL_MOVE_1, 5, 1, 5);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_2.png", eSpriteID::BILL_MOVE_2, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_3.png", eSpriteID::BILL_MOVE_3, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_4.png", eSpriteID::BILL_MOVE_4, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_5.png", eSpriteID::BILL_MOVE_5, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bullet.png", eSpriteID::BULLET_BIG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\FBullet.png", eSpriteID::F_BULLET, 4, 1, 4);

	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.png", eSpriteID::MAP_1, 92, 1, 92);
}

void SpriteManager::Release()
{
	map<eSpriteID, CSpriteDx9*>::iterator i;
	for(i = m_ListSprite.begin(); i != m_ListSprite.end(); i++)
	{
		i->second->Release();
		SAFE_DELETE(i->second);
	}
	m_ListSprite.clear();
}

SpriteManager::~SpriteManager(void)
{
}
