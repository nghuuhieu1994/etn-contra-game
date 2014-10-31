#ifndef __SceneManagerDx9_H__
#define __SceneManagerDx9_H__

#include "GameScene.h"
#include "CGameLog.h"
#include "CGlobal.h"
#include <vector>
class GameScene;

class SceneManagerDx9
{
private:
	
	SceneManagerDx9() {}
	
	~SceneManagerDx9() {}
	
	vector<GameScene*> m_ListGameScene;
	
	static SceneManagerDx9* s_Instance;
	
	LPDIRECT3DDEVICE9		m_lpDirectDevice;

public:
	
	static SceneManagerDx9* getInstance();
	
	void setDirectDevice(const LPDIRECT3DDEVICE9& lpDirectDevice);
	
	void Initialize();
	
	void HandleInput();
	
	void Update();
	
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	
	void AddElement(GameScene* GameScene);
	
	void ExitState();

	void ReplaceBy(GameScene* GameScene);
	
	void ClearAll();
};

#endif