#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#define			WIDTH		800
#define			HEIGHT		600
#define			FRAME_RATE	60
#define			GAMETITLE	"Tran Danh"
	
typedef enum eSpriteEffect
{
	Horizontally,  
	Vertically, 
	None
};

typedef enum eSoundID
{
	BROKEN
};

class CGlobal
{
public:
	static bool IsWindowMode;
	static bool IsExit;
	static bool IsMute;
};
#endif