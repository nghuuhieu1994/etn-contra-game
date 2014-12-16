#include "SoundMangerDx9.h"

SoundManagerDx9* SoundManagerDx9::s_Instace = 0;
bool CSoundSwitch::IsExit = false;
bool CSoundSwitch::IsMute = false;

SoundManagerDx9* SoundManagerDx9::getInstance()
{
	if ( s_Instace == 0 )
	{
		s_Instace = new SoundManagerDx9();
	}
	return s_Instace;
}

void SoundManagerDx9::LoadSoundBuffer(const char* fileName, eSoundID eID, LPDIRECTSOUND8 _lpDSound)
{
	SoundBuffer* _soundbuffer = new SoundBuffer();
	_soundbuffer->LoadWaveToBuffer(_lpDSound, (char*)fileName);
	_soundbuffer->getSoundBuffer()->SetVolume(m_Volume);
	m_ListSoundBuffer[eID] = _soundbuffer;
}

void SoundManagerDx9::LoadAllSoundBuffer(LPDIRECTSOUND8 _lpDSound)
{
	this->LoadSoundBuffer("resources\\Sound\\e_broken.wav", eSoundID::BROKEN, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\e_broken.wav", eSoundID::THU_CUOI_SONG, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\s_Theme_S_1.wav", eSoundID::THEME_SONG_S_1, _lpDSound);

	this->LoadSoundBuffer("resources\\Sound\\bullet_S_sfx.wav", eSoundID::bullet_S_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bullet_M_sfx.wav", eSoundID::bullet_M_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bridge_burn_sfx.wav", eSoundID::bridge_burn_sfx, _lpDSound);

	this->LoadSoundBuffer("resources\\Sound\\bullet_default_sfx.wav", eSoundID::bullet_default_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\boss_dead_sfx.wav", eSoundID::boss_dead_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\enemy_attacked_sfx.wav", eSoundID::enemy_attacked_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rambo_1up_sfx.wav", eSoundID::rambo_1up_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rambo_dead_sfx.wav", eSoundID::rambo_dead_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bullet_L_sfx.wav", eSoundID::bullet_L_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rambo_step_sfx.wav", eSoundID::rambo_step_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\enemy_dead_sfx.wav", eSoundID::enemy_dead_sfx, _lpDSound);

	this->LoadSoundBuffer("resources\\Sound\\bridge_exploision_sfx.wav", eSoundID::bridge_exploision_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\enemy_dead_sfx.wav", eSoundID::enemy_dead_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\boom_sfx.wav", eSoundID::boom_sfx, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_s2.wav", eSoundID::s_theme_s2, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_gameover.wav", eSoundID::s_theme_gameover, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_them_menu.wav", eSoundID::s_them_menu, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_fall.wav", eSoundID::s_theme_fall, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_s3.wav", eSoundID::s_theme_s3, _lpDSound);

	// need more and more sound rs

}
SoundBuffer* SoundManagerDx9::getSoundBuffer(eSoundID eID)
{
	map<eSoundID, SoundBuffer*>::iterator i;
	i = m_ListSoundBuffer.find(eID);
	if(i == m_ListSoundBuffer.end())
		return 0;
	return i->second;
}

void SoundManagerDx9::SetVolume(long volume)
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
void SoundManagerDx9::SetMute(bool isMute)
{
	CSoundSwitch::IsMute = isMute;
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
	SetVolume(m_Volume);
}
void SoundManagerDx9::DownVolume()
{
	if(m_Volume < -9900)
		m_Volume = -9900;
	m_Volume -= 100;
	SetVolume(m_Volume);
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