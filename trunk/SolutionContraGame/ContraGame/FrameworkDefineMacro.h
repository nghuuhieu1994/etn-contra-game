#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#define SCREEN_HEIGHT 448

#define SCREEN_WIDTH 512

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=0; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=0; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=0; }

#define DELAY_TIME_GUN_ROTATE 500

#define VELOC_WEAPONRY_X		1.0f
#define VELOC_WEAPONRY_Y		5.0f
#define ACCEL_WEAPONRY_Y		-0.07f



#ifndef SPRITEHANDLE
#define	SPRITEHANDLE LPD3DXSPRITE
#endif // SPRITEHANDLE

#define	GAMETITLE	"Contra"
#define	FRAME_RATE	60

#define DIRECTINPUT_HEADER_VERSION  0x0800

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION         DIRECTINPUT_HEADER_VERSION
#endif // DIRECTINPUT_VERSION

//initialize value of variable in this struct in SoundManager.cpp
#ifndef __CSOUNDSWITCH__
#define __CSOUNDSWITCH__
struct CSoundSwitch
{
	static bool IsExit;
	static bool IsMute;
};
#endif // __CSOUNDSWITCH__

#endif // __FRAMEWORK_H__