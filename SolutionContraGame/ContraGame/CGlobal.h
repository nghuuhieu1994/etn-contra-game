#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		448
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
	SPRITE_BIG_GUN_ROATING = 0,
	SPRITE_BOSS_CENTER = 1,
	SPRITE_BULLET_BIG,
	SPRITE_ENEMY_RUN,
	SPRITE_EXPLOISION,
	SPRITE_F_BULLET,
	SPRITE_GIF_BULLET_MOVING,
	SPRITE_GIF_BULLET_STATIC,
	SPRITE_GRID,
	SPRITE_GUN_BOSS,
	SPRITE_GUN_ROTATING,
	SPRITE_ICON,
	SPRITE_MAP_1,
	SPRITE_MENUBG,
	SPRITE_RAMBO_IDLE,
	SPRITE_RAMBO_JUMP,
	SPRITE_RAMBO_LIE,
	SPRITE_RAMBO_MOVE_BODY,
	SPRITE_RAMBO_MOVE_LEG,
	SPRITE_RAMBO_RUN,
	SPRITE_RAMBO_SHOOT_BODY,
	SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT,
	SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT_BODY,
	SPRITE_RAMBO_SHOOT_RUN,
	SPRITE_RAMBO_SHOOT_TOP_RIGHT,
	SPRITE_RAMBO_SHOOT_TOP_RIGHT_BODY,
	SPRITE_RAMBO_SHOOT_UP,
	SPRITE_RAMBO_SHOOT_UP_BODY,
	SPRITE_SNIPER_HIDING,
	SPRITE_SNIPER_SHOOTING,
	SPRITE_SNIPER_STANDING_BOT,
	SPRITE_SNIPER_STANDING_MID,
	SPRITE_SNIPER_STANDING_TOP,
	// End all ID Enemy Sprite

};

enum eObjectState
{
	STATE_ALIVE_IDLE = 0,
	STATE_ALIVE_MOVE = 1,
	STATE_BEFORE_DEATH,
	STATE_DEATH,
	STATE_RAMBO_AIM_BOTTOM_RIGHT,
	STATE_RAMBO_AIM_TOP_RIGHT,
	STATE_RAMBO_AIM_UP,
	STATE_RAMBO_IDLE,
	STATE_RAMBO_JUMP,
	STATE_RAMBO_LIE,
	STATE_RAMBO_MOVE,
	STATE_RAMBO_RUN,
	STATE_RAMBO_SHOOT,
	STATE_RAMBO_SHOOT_RUN,
	STATE_SHOOTING, // dm deo them cai nay sao xet cho no ban?
};

enum eObjectID
{
	TILE_BASE,
	RAMBO,
	BULLET_RAMBO,
	BULLET_ENEMY,
	SNIPER_STANDING,
	SNIPER_HIDING,
	GIF_BULLET_STATIC,
	GIF_BULLET_MOVING,
	GUN_ROTATING,
	BIG_GUN_ROTATING,
	ENEMY_RUN,
	BOSS_GUN,
	BOSS_CENTER,
};


enum eDirection
{
	BOTTOM = 0,
	LEFT = 1,
	RIGHT,
	TOP,
};

//dm thang nao code cai deo nay vay??? =))
typedef enum eDirectAttack
{
	NONE = 0,
	NORTH = 1, // Bac // TOP
	SOUTH, // Nam //BOTTOM
	EAST, // Dong //RIGHT
	WEST, // Tay //LEFT
	NORTH_EAST, // Bac > Dong //TOP > RIGHT
	EAST_NORTH, // Dong > Bac //RIGHT > TOP
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

enum eIDSceneGame
{
	INTRO = 0,
	TEST_SPRITE = 1,
	MENUGAME
};

class CGlobal
{
public:
	static bool IsExit;
	static bool IsMute;
	static bool IsWindowMode;
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
	DIR_ANONYMOUS,
	DIR_BOTTOM,
	DIR_LEFT,
	DIR_NONE,
	DIR_RIGHT,
	DIR_TOP,
};

bool IsMovementObject(int type);

#endif