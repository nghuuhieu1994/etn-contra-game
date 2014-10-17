#include "CObjectDx9.h"
#include "CGlobal.h"
#ifndef __TILE_H__
#define __TILE_H__

class Tile : public Object
{
public:
	Tile(void);
	Tile(D3DXVECTOR3 _position, int _ID, eSpriteID tileMapID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);

	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Tile(void);
};

#endif