#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		512
#define			FRAME_RATE	60
#define			GAMETITLE	"Contra"

#define			TURN_ON_UPDATE_SPRITE(p)		p = p | (1 << 0)
#define			TURN_OFF_UPDATE_SPRITE(p)		p = p ^ (1 << 0)
#define			IS_UPDATE_SPRITE(p)				p & (1 << 0)

#ifndef SPRITEHANDLE
#define			SPRITEHANDLE LPD3DXSPRITE
#endif // !1

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=0; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=0; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=0; }

#define DIRECTINPUT_HEADER_VERSION  0x0800
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION         DIRECTINPUT_HEADER_VERSION
//#pragma message(__FILE__ ": DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800")
#endif

#ifndef TILE_WIDTH
#define TILE_WIDTH 64
#endif

#ifndef TILE_HEIGHT
#define TILE_HEIGHT 64
#endif

enum ESpriteEffect
{
	None = 0,
	Horizontally = 1,  
	Vertically = 2, 
};

enum eSoundID
{
	BROKEN = 0,
	THU_CUOI_SONG = 1,
	THEME_SONG_S_1
};

enum eSpriteID
{
	SPRITE_RAMBO_JUMP = 0,
	SPRITE_RAMBO_LIE = 1,
	SPRITE_RAMBO_SHOOT_UP,
	SPRITE_RAMBO_SHOOT_RUN,
	SPRITE_RAMBO_SHOOT_TOP_RIGHT,
	SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT,
	SPRITE_RAMBO_IDLE,
	SPRITE_RAMBO_RUN,
	SPRITE_BULLET_BIG,
	SPRITE_F_BULLET,
	SPRITE_MAP_1,

	SPRITE_MENUBG,
	SPRITE_ICON,
	SPRITE_GRID,

	// All ID Enemy Sprite
	SPRITE_EXPLOISION,
	SPRITE_SNIPER_STANDING_BOT,
	SPRITE_SNIPER_STANDING_TOP,
	SPRITE_SNIPER_STANDING_MID,

	SPRITE_GUN_1,
	SPRITE_GUN_2,
	SPRITE_FLYER_SIN,

	// End all ID Enemy Sprite

};

enum eObjectState
{
	STATE_ALIVE_IDLE = 0,
	STATE_ALIVE_MOVE = 1,
	STATE_SHOOTING, // dm deo them cai nay sao xet cho no ban?
	STATE_BEFORE_DEATH,
	STATE_DEATH,
	
	STATE_RAMBO_JUMP,
	STATE_RAMBO_LIE,
	STATE_RAMBO_SHOOT,
	STATE_RAMBO_SHOOT_UP,
	STATE_RAMBO_SHOOT_RUN,
	STATE_RAMBO_SHOOT_TOP_RIGHT,
	STATE_RAMBO_SHOOT_BOTTOM_RIGHT,
	STATE_RAMBO_IDLE,
	STATE_RAMBO_RUN,
};

enum eObjectID
{
	TILE_BASE,
	RAMBO,
	BULLET_RAMBO,
	BULLET_ENEMY,
	SNIPER_STANDING,
	GUN_1,
	FLYER_SIN,
};

enum eDirection
{
	TOP = 0,
	BOTTOM = 1,
	LEFT,
	RIGHT,
};

enum eIDStateGame
{
	INTRO = 0,
	TEST_SPRITE = 1,
	MENUGAME
};

class CGlobal
{
public:
	static bool IsWindowMode;
	static bool IsExit;
	static bool IsMute;
	static int	Rambo_X;
	static int	Rambo_Y;
};

#endif