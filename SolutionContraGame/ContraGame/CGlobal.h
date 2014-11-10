#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

//#define			WIDTH		800
//#define			HEIGHT		448
//
//#define			GAMETITLE	"Contra"
//
//#ifndef SPRITEHANDLE
//#define			SPRITEHANDLE LPD3DXSPRITE
//#endif
//
//#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=0; }
//
//#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=0; }
//
//#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=0; }
//
//#define DIRECTINPUT_HEADER_VERSION  0x0800
//#ifndef DIRECTINPUT_VERSION
//#define DIRECTINPUT_VERSION         DIRECTINPUT_HEADER_VERSION
//
//#endif

class CGlobal
{
public:
	static bool IsExit;
	static bool IsMute;
	static bool IsWindowMode;
	static int	Rambo_X;
	static int	Rambo_Y;
};

bool IsMovementObject(int type);

#endif