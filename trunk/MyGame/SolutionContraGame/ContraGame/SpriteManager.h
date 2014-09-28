#include "CSpriteDx9.h"

#ifndef __SPRITE_MANAGER__
#define __SPRITE_MANAGER__

class SpriteManager
{
	SpriteManager(void);
	static SpriteManager* s_Instance;
	CSpriteDx9* Bill;
public:
	static SpriteManager* GetInstance();
	void LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice);
	~SpriteManager(void);
};

#endif