#pragma once
#include "gamescene.h"
class LoseState :
	public GameScene
{
	LPD3DXFONT m_Font;
	int m_currentStage;
	CSpriteDx9* m_Icon;
	D3DXVECTOR3 m_IconPosition;
public:
	LoseState(eIDSceneGame _ID, int currentStage);
	~LoseState(void);
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

