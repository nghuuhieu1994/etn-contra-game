#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		600
#define			FRAME_RATE	60
#define			GAMETITLE	"Contra"

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=NULL; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=NULL; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=NULL; }

#define DIRECTINPUT_VERSION 0X0800

typedef enum eSpriteEffect
{
	None = 0,
	Horizontally = 1,  
	Vertically = 2, 
};

typedef enum eSoundID
{
	BROKEN = 0,
};

typedef enum eSpriteID
{
	BILL_JUMP = 0,
	BILL_LIE_DOWN = 1,
	BILL_MOVE_1,
	BILL_MOVE_2,
	BILL_MOVE_3,
	BILL_MOVE_4,
	BILL_MOVE_5,
};

typedef enum eIDStateGame
{

};

class CGlobal
{
public:
	static bool IsWindowMode;
	static bool IsExit;
	static bool IsMute;
};

#endif