#ifndef __CSPRITE_H__
#define __CSPRITE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "CTextureDx9.h"
#include "CAnimationDx9.h"
#include "SpriteEffect.h"
#include <vector>

using namespace std;

class CSpriteDx9
{
private:
	vector<RECT> m_listSourceRectangle;
	//Direct3D texture
	//CTextureDx9*		m_texture;

	LPDIRECT3DTEXTURE9	m_lpDTexture;
	
	//Save info of texture
	D3DXIMAGE_INFO		m_Info;

	// Hold the animation action
	CAnimationDx9*		m_animation;

	// Total frame in this sheet Image
	int					m_totalFrameOfSprite;

	int					m_alphaRender;
	int					m_alphaOffsetPerFrame;
public:
	CSpriteDx9();
	CSpriteDx9(D3DXVECTOR3* Position, LPCSTR fileName, D3DCOLOR  color, int ColFrame, int RowFrame, int TotalFrame);
	CSpriteDx9(const CSpriteDx9* otherSprite);
	//---------------------------------------------------
	/// @desciption: use this function to get data of sprite(frameWidth, frameHeight...)
	/// @param frameWidth: width of 1 frame
	/// @param frameHeight: height of 1 frame
	/// @param sheetColumn: Column of texture
	/// @param sheetRow: Row of texture
	/// @param totalFrameOfSprite: total frame of entire texture
	//---------------------------------------------------
	void InitializeSpriteData(int frameWidth, int frameHeight, int sheetColumn, int sheetRow, int totalFrameOfSprite);
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	void LoadTexture(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName);
	void Effect(LPD3DXSPRITE spriteBatch, D3DXVECTOR3* center, D3DXVECTOR3* location);
	//void Render(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSprite);
	CAnimationDx9* getAnimation();
	//---------------------------------------------------
	/// This function contains blablabla...
	//---------------------------------------------------
	void Render(LPD3DXSPRITE _SpriteBatch, D3DXVECTOR3* _Location);
	void Render(LPD3DXSPRITE spriteBatch, D3DXVECTOR3* location, void(*spriteEffect)(D3DXMATRIX*, RECT* frameRect));
};


#endif