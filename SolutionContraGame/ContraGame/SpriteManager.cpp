#include "SpriteManager.h"

#define INCLUDE_MAP1 LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.png", eSpriteID::SPRITE_MAP_1, 42, 1, 42)
#define INCLUDE_MAP2 LoadSpriteContent(_lpDirectDevice, "resources\\Map\\2\\2.png", eSpriteID::SPRITE_MAP_2, 46, 1, 46)
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

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_idle.png", eSpriteID::SPRITE_RAMBO_IDLE, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_lie.png", eSpriteID::SPRITE_RAMBO_LIE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_run.png", eSpriteID::SPRITE_RAMBO_RUN, 6, 1, 6);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_bottom_right.png", eSpriteID::SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_run.png", eSpriteID::SPRITE_RAMBO_SHOOT_RUN, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_top_right.png", eSpriteID::SPRITE_RAMBO_SHOOT_TOP_RIGHT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_up.png", eSpriteID::SPRITE_RAMBO_SHOOT_UP, 2, 1, 2);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\bullet.png", eSpriteID::SPRITE_BULLET_BIG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\FBullet.png", eSpriteID::SPRITE_F_BULLET, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\default_bullet_rambo.png", eSpriteID::SPRITE_DEFAULT_BULLET_RAMBO, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\fire.png", eSpriteID::SPRITE_FIRE_BULLET_RAMBO, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Landscape\\ledframe.png", eSpriteID::SPRITE_LED_OBJECT, 2, 1, 2);
	INCLUDE_MAP1;
	INCLUDE_MAP2;
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\bg.png", eSpriteID::SPRITE_MENUBG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\icon.png", eSpriteID::SPRITE_ICON, 1, 1, 1);

	LoadSpriteContent(_lpDirectDevice, "resources\\grid.png", eSpriteID::SPRITE_GRID, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\lazer.png", eSpriteID::SPRITE_LAZE_BULLET_RAMBO, 2, 2, 4);
	// start the fucking bridge

	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\BodyBridge.png", eSpriteID::SPRITE_BRIDGE_BODY, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\HeadBridge.png", eSpriteID::SPRITE_BRIDGE_HEAD, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\TailBridge.png", eSpriteID::SPRITE_BRIDGE_TAIL, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\head_bridge_broken.png", eSpriteID::SPRITE_HEAD_BREAK, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\tail_bridge_broken.png", eSpriteID::SPRITE_TAIL_BREAK, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\BridgeExploision.png", eSpriteID::SPRITE_BRIDGE_EXPLOISION, 5, 3, 15);
	// end load the fucking bridge

	// Start load EnemyContent
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Exploision.png", eSpriteID::SPRITE_EXPLOISION, 6, 1, 6);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\SniperStanding\\SniperStanding_bot.png", eSpriteID::SPRITE_SNIPER_STANDING_BOT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\SniperStanding\\SniperStanding_top.png", eSpriteID::SPRITE_SNIPER_STANDING_TOP, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\SniperStanding\\SniperStanding_mid.png", eSpriteID::SPRITE_SNIPER_STANDING_MID, 2, 1, 2);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\SniperHiding\\SniperHiding.png", eSpriteID::SPRITE_SNIPER_HIDING, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\SniperHiding\\SniperHidingDead.png", eSpriteID::SPRITE_SNIPER_HIDING_EXPLOISION, 4, 1, 4);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\SnipperWaterHiding\\SnipperWaterHiding.png", eSpriteID::SPRITE_SNIPER_WATER_HIDING, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\SniperShooting\\SniperShooting.png", eSpriteID::SPRITE_SNIPER_SHOOTING, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRun\\EnemyRun.png", eSpriteID::SPRITE_ENEMY_RUN, 6, 1, 6);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRunShooting\\EnemyRunShooting.png", eSpriteID::SPRITE_ENEMY_RUN_SHOOTING, 6, 1, 6);

	// Weapon
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\WeaponSensor.png", eSpriteID::SPRITE_WEAPON_SENSOR, 7, 1, 7);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\WeaponCapsule.png", eSpriteID::SPRITE_WEAPON_CAPSULE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\Barrier.png", eSpriteID::SPRITE_BARRIER, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\RapidFire.png", eSpriteID::SPRITE_RAPID_FIRE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\SpreadGun.png", eSpriteID::SPRITE_SPREAD_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\LaserGun.png", eSpriteID::SPRITE_LASER_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\MachineGun.png", eSpriteID::SPRITE_MACHINE_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\FlameGun.png", eSpriteID::SPRITE_FLAME_GUN, 1, 1, 1);
	// End Weapon

	// Gunrotating
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\GunRotating.png", eSpriteID::SPRITE_GUN_ROTATING, 14, 1, 14);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\bigGunRotating.png", eSpriteID::SPRITE_BIG_GUN_ROATING, 3, 3, 9);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\bigGunRotatingPopup.png", eSpriteID::SPRITE_BIG_GUN_ROTAING_POPUP, 3, 2, 6);
	// End Gunrotating

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\Move\\move.png", eSpriteID::SPRITE_RAMBO_MOVE_BODY, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Leg\\Move\\move.png", eSpriteID::SPRITE_RAMBO_MOVE_LEG, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\MoveUp\\top_right.png", eSpriteID::SPRITE_RAMBO_SHOOT_TOP_RIGHT_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\MoveDown\\bottom_right.png", eSpriteID::SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\shoot.png", eSpriteID::SPRITE_RAMBO_SHOOT_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\up.png", eSpriteID::SPRITE_RAMBO_SHOOT_UP_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\jump.png", eSpriteID::SPRITE_RAMBO_JUMP, 4, 1, 4);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\water_bomb.png", eSpriteID::SPRITE_RAMBO_WATER_BOMB, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\climb.png", eSpriteID::SPRITE_RAMBO_CLIMB, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\dive.png", eSpriteID::SPRITE_RAMBO_DIVE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\swim.png", eSpriteID::SPRITE_RAMBO_SWIM, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\RamboSplit\\Body\\dead.png", eSpriteID::SPRITE_RAMBO_BEFORE_DEAD, 5, 1, 5);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\GunBoss\\BossGun.png", eSpriteID::SPRITE_GUN_BOSS, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossCenter\\BossCenter.png", eSpriteID::SPRITE_BOSS_CENTER, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossBodyDead.png", eSpriteID::SPRITE_BOSS_BODY_DEAD, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossBodyAlive.png", eSpriteID::SPRITE_BOSS_BODY_ALIVE, 1, 1, 1);
	//BOSS MAP 3
		LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap3\\SpaceShip.png", eSpriteID::SPRITE_SPACE_SHIP, 3, 1, 3);
	//END BOSSMAP3
	LoadSpriteContent(_lpDirectDevice, "resources\\Items\\medal.png", eSpriteID::SPRITE_MEDAL, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.effect", eSpriteID::SPRITE_EFFECT_MAP1, 1, 2, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\2\\2.effect", eSpriteID::SPRITE_EFFECT_MAP2, 3, 1, 3);
	
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
