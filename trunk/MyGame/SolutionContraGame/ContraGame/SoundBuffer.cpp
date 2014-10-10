#include "SoundBuffer.h"
#include "CGameLog.h"
#include "DSutil.h"
#include "CGlobal.h"
SoundBuffer::SoundBuffer()
{
	this->m_SoundBuffer = NULL;
}

SoundBuffer::~SoundBuffer()
{
	SAFE_RELEASE(m_SoundBuffer);
}

bool SoundBuffer::LoadWaveToBuffer(LPDIRECTSOUND8 _lpDSound, const char* fileName)
{
	CWaveFile* waveFile = new CWaveFile();
	HRESULT hr;

	hr = waveFile->Open((char*)fileName, NULL, WAVEFILE_READ);

	if FAILED(hr)
	{
		CGameLog::getInstance("LoadWaveToBuffer")->SaveInfo("Can't find File");
		return false;
	}
	DSBUFFERDESC _dsbd;
	ZeroMemory(&_dsbd, sizeof(DSBUFFERDESC));
	_dsbd.dwSize		= sizeof(DSBUFFERDESC);
	_dsbd.dwFlags		= DSBCAPS_CTRLVOLUME;
	_dsbd.dwBufferBytes	= waveFile->GetSize();
	_dsbd.guid3DAlgorithm = GUID_NULL;
	_dsbd.lpwfxFormat	= waveFile->m_pwfx;

	hr = _lpDSound->CreateSoundBuffer(&_dsbd, &m_SoundBuffer, NULL);
	if FAILED(hr)
	{
		CGameLog::getInstance("LoadWaveToBuffer")->SaveInfo("Can't Create Sound Buffer");
		return false;
	}
	VOID*	pDSLockedBuffer			= NULL; // pointer to a locked buffer memory
	DWORD	dwDSLockedBufferSize	= 0;	// Size of the locked DirectSound buffer
	DWORD	dwWavDataRead			= 0; // Amount of data from the wav file

	hr = m_SoundBuffer->Lock(0, waveFile->GetSize(), &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0L);

	if FAILED(hr)
	{
		CGameLog::getInstance("LoadWaveToBuffer")->SaveInfo("Can't Lock device");
		return false;
	}

	// Res the wave file to the begin
	waveFile->ResetFile();

	// Read the wave File
	hr = waveFile->Read( (BYTE*)pDSLockedBuffer, 
							dwDSLockedBufferSize,
							&dwWavDataRead ) ;
	if FAILED(hr)
	{
		CGameLog::getInstance("LoadWaveToBuffer")->SaveInfo("Can't Read");
		return false;
	}

	if (dwWavDataRead == 0)
	{
		// Wave is blank, so just fill with silence
		FillMemory( (BYTE*) pDSLockedBuffer, 
			dwDSLockedBufferSize,
			(BYTE) (waveFile->m_pwfx->wBitsPerSample = 8 ? 128 : 0));
	} else if( dwWavDataRead < dwDSLockedBufferSize)
	{
		// DOn't repeat the wav file, just fill in slience
		FillMemory( (BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE) (waveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 8) );
	}

	// unlock buffer
	m_SoundBuffer->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);
	// clean
	delete waveFile;

	return true;
}

void SoundBuffer::Play()
{
	if(!CGlobal::IsMute)
		m_SoundBuffer->Play(0, 0, 0);
}
void SoundBuffer::Repeat()
{
	if(!CGlobal::IsMute)
		m_SoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
}
void SoundBuffer::Stop()
{
	m_SoundBuffer->Stop();
}
LPDIRECTSOUNDBUFFER SoundBuffer::getSoundBuffer()
{
	return m_SoundBuffer;
}
void SoundBuffer::Release()
{
	SAFE_RELEASE(m_SoundBuffer);
}