#ifndef __SOUNDBUFFER_H__
#define __SOUNDBUFFER_H__

#include <dsound.h>
#include <d3d.h>
#include <d3d9.h>
#include <string>
#include <string.h>
using namespace std;

class SoundBuffer
{
private:
	LPDIRECTSOUNDBUFFER m_SoundBuffer;
public:
	SoundBuffer();
	~SoundBuffer();

	bool LoadWaveToBuffer(LPDIRECTSOUND8 lpDSound, const char* FileName);
	LPDIRECTSOUNDBUFFER getSoundBuffer();
	void Play();
	void Repeat();
	void Stop();
};

#endif