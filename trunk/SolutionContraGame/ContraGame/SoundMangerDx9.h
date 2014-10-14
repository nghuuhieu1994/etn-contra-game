#ifndef __SOUNDMANAGERDX9_H__
#define __SOUNDMANAGERDX9_H__

#include "SoundBuffer.h"
#include "CGlobal.h"
#include "CGameLog.h"
#include <map>

class SoundManagerDx9
{
private:
	map<eSoundID, SoundBuffer*> m_ListSoundBuffer;
	long		m_Volume;
	bool		m_IsMute;

	SoundManagerDx9() {m_Volume = 0; m_IsMute = false;}
	static SoundManagerDx9* s_Instace;
	void LoadSoundBuffer(const char* fileName, eSoundID eID, LPDIRECTSOUND8 _lpDSound);
public:
	static SoundManagerDx9* getInstance();
	void LoadAllSoundBuffer(LPDIRECTSOUND8 _lpDSound);

	SoundBuffer* getSoundBuffer(eSoundID eID);

	void SetVolume(long volume);
	void SetMute(bool isMute);
	void UpVolume();
	void DownVolume();
	void Release();
};


#endif