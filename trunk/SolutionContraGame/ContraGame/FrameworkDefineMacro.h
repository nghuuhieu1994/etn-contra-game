#define SCREEN_HEIGHT 448
#define SCREEN_WIDTH 800

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=0; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=0; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=0; }

#ifndef SPRITEHANDLE
#define	SPRITEHANDLE LPD3DXSPRITE
#endif

#define	FRAME_RATE	60

//initialize value of variable in this struct in SoundManager.cpp
#ifndef __CSOUNDSWITCH__
#define __CSOUNDSWITCH__
struct CSoundSwitch
{
	static bool IsExit;
	static bool IsMute;
};
#endif