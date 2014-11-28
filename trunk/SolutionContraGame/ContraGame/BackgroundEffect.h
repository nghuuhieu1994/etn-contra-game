#ifndef __BACKGROUND_EFFECT_H__
#define __BACKGROUND_EFFECT_H__

#include "SpriteManager.h"

class BackgroundEffect
{
private:
	CSpriteDx9* m_Sprite;
	float timeStar;
	float delayStar;
public:
	BackgroundEffect();
	~BackgroundEffect();
	void Initialize(int _tile_effect);
	RECT getSourceRectEffect(RECT cameraRect, RECT sourceFrame);
	void UpdateAnimation();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
};

#endif