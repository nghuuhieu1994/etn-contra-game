#include "SoundMangerDx9.h"
#include "CGlobal.h"
SoundManagerDx9* SoundManagerDx9::m_Instace = NULL;

SoundManagerDx9* SoundManagerDx9::getInstance()
{
	if ( m_Instace == 0 )
	{
		m_Instace = new SoundManagerDx9();
	}
	return m_Instace;
}

void SoundManagerDx9::LoadSoundBuffer(const char* fileName, eSoundID eID, LPDIRECTSOUND8 lpDSound)
{
	SoundBuffer* _soundbuffer = new SoundBuffer();
	_soundbuffer->LoadWaveToBuffer(lpDSound, (char*)fileName);
	_soundbuffer->getSoundBuffer()->SetVolume(m_Volume);
	m_ListSoundBuffer[eID] = _soundbuffer;
}
void SoundManagerDx9::LoadAllSoundBuffer(LPDIRECTSOUND8 lpDSound)
{
	this->LoadSoundBuffer("resources\\Sound\\e_broken.wav", eSoundID::BROKEN, lpDSound);
	// need more and more sound rs
}
SoundBuffer* SoundManagerDx9::getSoundBuffer(eSoundID eID)
{
	map<eSoundID, SoundBuffer*>::iterator i;
	i = m_ListSoundBuffer.find(eID);
	if(i == m_ListSoundBuffer.end())
		return NULL;
	return i->second;
}

void SoundManagerDx9::setVolume(long volume)
{
	if(volume < -10000)
		volume = -10000;
	if(volume > 0)
		volume = 0;
	this->m_Volume = volume;

	map<eSoundID, SoundBuffer*>::iterator i;
	for(i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
		i->second->getSoundBuffer()->SetVolume(m_Volume);
	// ve nha code tiep
}
void SoundManagerDx9::setMute(bool isMute)
{
	CGlobal::IsMute = isMute;
	map<eSoundID, SoundBuffer*>::iterator i;
	if(isMute)
	{
		for(i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
			i->second->getSoundBuffer()->SetVolume(-10000);
	}
}
void SoundManagerDx9::UpVolume()
{
	if(m_Volume > -9900)
		m_Volume = -9900;
	m_Volume += 100;
	setVolume(m_Volume);
}
void SoundManagerDx9::DownVolume()
{
	if(m_Volume < -9900)
		m_Volume = -9900;
	m_Volume -= 100;
	setVolume(m_Volume);
}

void SoundManagerDx9::Release()
{
	map<eSoundID, SoundBuffer*>::iterator i;
	for(i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
	{
		i->second->Release();
		SAFE_DELETE(i->second);
	}
	m_ListSoundBuffer.clear();
}