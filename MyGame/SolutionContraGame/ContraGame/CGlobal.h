#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		600
#define			FRAME_RATE	60
#define			GAMETITLE	"Contra"
	
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