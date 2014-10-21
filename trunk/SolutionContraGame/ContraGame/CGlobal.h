#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		512
#define			FRAME_RATE	60
#define			GAMETITLE	"Contra"

#define			IS_UPDATE_SPRITE(p)				p & (1 << 0)
#define			TURN_OFF_UPDATE_SPRITE(p)		p = p ^ (1 << 0)
#define			TURN_ON_UPDATE_SPRITE(p)		p = p | (1 << 0)

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

	// All ID Enemy Sprite
	SPRITE_BULLET_BIG = 0,
	SPRITE_EXPLOISION = 1,
	SPRITE_F_BULLET,
	SPRITE_GIF_BULLET_MOVING,
	SPRITE_GRID,
	SPRITE_GIF_BULLET_STATIC,
	SPRITE_GUN_ROTATING,
	SPRITE_ICON,
	SPRITE_MAP_1,
	SPRITE_MENUBG,
	SPRITE_RAMBO_IDLE,
	SPRITE_RAMBO_JUMP,
	SPRITE_RAMBO_LIE,
	SPRITE_RAMBO_RUN,
	SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT,
	SPRITE_RAMBO_SHOOT_RUN,
	SPRITE_RAMBO_SHOOT_TOP_RIGHT,
	SPRITE_RAMBO_SHOOT_UP,
	SPRITE_SNIPER_STANDING_BOT,
	SPRITE_SNIPER_STANDING_MID,
	SPRITE_SNIPER_STANDING_TOP,
	SPRITE_ENEMY_RUN,

	// End all ID Enemy Sprite

};

enum eObjectState
{
	STATE_ALIVE_IDLE = 0,
	STATE_ALIVE_MOVE = 1,
	STATE_BEFORE_DEATH,
	STATE_DEATH,
	STATE_RAMBO_IDLE,
	STATE_RAMBO_JUMP,
	STATE_RAMBO_LIE,
	STATE_RAMBO_RUN,
	STATE_RAMBO_SHOOT,
	STATE_RAMBO_SHOOT_BOTTOM_RIGHT,
	STATE_RAMBO_SHOOT_RUN,
	STATE_RAMBO_SHOOT_TOP_RIGHT,
	STATE_RAMBO_SHOOT_UP,
	STATE_SHOOTING, // dm deo them cai nay sao xet cho no ban?
};

enum eObjectID
{
	TILE_BASE,
	RAMBO,
	BULLET_RAMBO,
	BULLET_ENEMY,
	SNIPER_STANDING,
	GIF_BULLET_STATIC,
	GIF_BULLET_MOVING,
	GUN_ROTATING,
	ENEMY_RUN,
};

enum eDirection
{
	TOP = 0,
	BOTTOM = 1,
	LEFT,
	RIGHT,
};

typedef enum eDirectAttack
{
	NONE = 0,
	NORTH = 1, // Bac
	SOUTH, // Nam
	EAST, // Dong
	WEST, // Tay
	NORTH_EAST, // Bac > Dong
	EAST_NORTH, // Dong > Bac
	NORTH_WEST, // Bac > Tay
	WEST_NORTH, // Tay > Bac
	WEST_SOUTH, // Tay > Nam
	SOUTH_WEST, // Nam > Tay
	SOUTH_EAST, // Nam > Dong
	EAST_SOUTH  // Dong > Nam
};

enum ETypeObject
{
	TILE_MAP = 0,
	VIRTUAL_OBJECT = 1,
	STATIC_OBJECT = 2,
	DYNAMIC_OBJECT = 3,
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


struct BOX
{
	float x;
	float y;
	float width;
	float height;
	float vx;
	float vy;

	BOX(float _x, float _y, float _width, float _height, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		vx = _vx;
		vy = _vy;
	}

	BOX(float _x, float _y, float _width, float _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		vx = 0.0f;
		vy = 0.0f;
	}

	BOX()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
		vx = 0.0f;
		vy = 0.0f;
	}
};

enum IDDirection
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_TOP,
	DIR_BOTTOM,
	DIR_ANONYMOUSE,
	DIR_NONE,
};

bool IsMovementObject(int type);

#endif