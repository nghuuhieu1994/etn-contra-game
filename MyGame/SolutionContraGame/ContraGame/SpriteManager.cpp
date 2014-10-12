#include "SpriteManager.h"

#define INCLUDE_MAP1 LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.png", eSpriteID::SPRITE_MAP_1, 45, 1, 45)

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

CSpriteDx9* SpriteManager::getSprite(eSpriteID eID)
{
	map<eSpriteID, CSpriteDx9*>::iterator i;

	i = m_ListSprite.find(eID);

	if(i == m_ListSprite.end())
		return 0;

	return i->second;
}

void SpriteManager::InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_jump.png", eSpriteID::SPRITE_BILL_JUMP, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_lie.png", eSpriteID::SPRITE_BILL_LIE_DOWN, 1, 1, 1);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_1.png", eSpriteID::SPRITE_BILL_MOVE_1, 6, 1, 6);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_2.png", eSpriteID::SPRITE_BILL_MOVE_2, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_3.png", eSpriteID::SPRITE_BILL_MOVE_3, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_move_4.png", eSpriteID::SPRITE_BILL_MOVE_4, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bill_idle.png", eSpriteID::SPRITE_BILL_IDLE, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\bullet.png", eSpriteID::SPRITE_BULLET_BIG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bill\\FBullet.png", eSpriteID::SPRITE_F_BULLET, 4, 1, 4);

	INCLUDE_MAP1;

	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\MenuBG.png", eSpriteID::SPRITE_MENUBG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\icon.png", eSpriteID::SPRITE_ICON, 1, 1, 1);

	LoadSpriteContent(_lpDirectDevice, "resources\\grid.png", eSpriteID::SPRITE_GRID, 1, 1, 1);

	// Start load EnemyContent
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Exploision.png", eSpriteID::SPRITE_EXPLOISION, 6, 1, 6);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\SniperStanding\\SniperStanding_bot.png", eSpriteID::SPRITE_SNIPER_STANDING_BOT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\SniperStanding\\SniperStanding_top.png", eSpriteID::SPRITE_SNIPER_STANDING_TOP, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\SniperStanding\\SniperStanding_mid.png", eSpriteID::SPRITE_SNIPER_STANDING_MID, 2, 1, 2);
	
	// End load EnemyContent

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\Gun_1.png", eSpriteID::SPRITE_GUN_1, 7, 1, 7);

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
