#ifndef __SOUNDMANAGERDX9_H__
#define __SOUNDMANAGERDX9_H__

#include "SoundBuffer.h"
#include "CGlobal.h"
#include <map>

class SoundManagerDx9
{
private:
	map<eSoundID, SoundBuffer*> m_ListSoundBuffer;
	long		m_Volume;
	bool		m_IsMute;
	
	SoundManagerDx9() {m_Volume = 0; m_IsMute = false;}
	static SoundManagerDx9* m_Instace;
public:
	static SoundManagerDx9* getInstance();
	void LoadAllSoundBuffer(LPDIRECTSOUND8 lpDSound);
	void LoadSoundBuffer(const char* fileName, eSoundID eID, LPDIRECTSOUND8 lpDSound);
	SoundBuffer* getSoundBuffer(eSoundID eID);
	void setVolume(long volume);
	void setMute(bool isMute);
	void UpVolume();
	void DownVolume();
};


#endif