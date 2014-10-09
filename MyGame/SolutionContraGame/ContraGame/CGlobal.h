#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		600
#define			FRAME_RATE	60
#define			GAMETITLE	"Contra"

#ifndef SPRITEHANDLE
#define			SPRITEHANDLE LPD3DXSPRITE
#endif // !1

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=NULL; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=NULL; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=NULL; }

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

typedef enum eSpriteEffect
{
	None = 0,
	Horizontally = 1,  
	Vertically = 2, 
};

typedef enum eSoundID
{
	BROKEN = 0,
	THU_CUOI_SONG = 1,
	THEME_SONG_S_1
};

typedef enum eSpriteID
{
	SPRITE_BILL_JUMP = 0,
	SPRITE_BILL_LIE_DOWN = 1,
	SPRITE_BILL_MOVE_1,
	SPRITE_BILL_MOVE_2,
	SPRITE_BILL_MOVE_3,
	SPRITE_BILL_MOVE_4,
	SPRITE_BILL_IDLE,
	SPRITE_BULLET_BIG,
	SPRITE_F_BULLET,
	SPRITE_MAP_1,

	SPRITE_MENUBG,
	SPRITE_ICON,
	SPRITE_GRID,
};

typedef enum eObjectState
{
	STATE_ALIVE = 0,
	STATE_DEATH = 1,
	STATE_BILL_MOVE_1,	
	STATE_BILL_MOVE_2,
	STATE_BILL_MOVE_3,
	STATE_BILL_MOVE_4,
	STATE_BILL_IDLE,
	STATE_BILL_JUMP,
	STATE_BILL_LIE_DOWN,
};

typedef enum eObjectID
{

};

typedef enum eDirection
{
	TOP = 0,
	BOTTOM = 1,
	LEFT,
	RIGHT,
};

typedef enum eIDStateGame
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
};

#endif