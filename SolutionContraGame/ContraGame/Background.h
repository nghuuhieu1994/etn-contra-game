#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
//#include "CGameLog.h"
//#include "SpriteManager.h"
//#include "CSpriteDx9.h"
//#include "CGlobal.h"
#include "Markup.h"
//#include <list>

//using namespace std;
class GameObject
{
public:
	int _ID;
	int _X;
	int _Y;
	int _Type;
	int m_Width;
	int m_Height;
public:
	void Deserialize(const char *childContent)
	{
		CMarkup xml(childContent);
		xml.FindElem();
		//_ID = atoi(xml.GetAttrib("Id").c_str());
		_Type = atoi(xml.GetAttrib("Type").c_str());
		//_X = atoi(xml.GetAttrib("X").c_str());
		//_Y = atoi(xml.GetAttrib("Y").c_str());
	}
	void DeserializeVirtualObject(const char* childContent)
	{
		CMarkup xml(childContent);
		xml.FindElem();
		_ID			= atoi(xml.GetAttrib("Id").c_str());
		_Type		= atoi(xml.GetAttrib("Type").c_str());
		_X			= atoi(xml.GetAttrib("X").c_str());
		_Y			= atoi(xml.GetAttrib("Y").c_str());
		m_Height	= atoi(xml.GetAttrib("Height").c_str());
		m_Width		= atoi(xml.GetAttrib("Width").c_str());
	}
	void DeserializeTile(const char *childContent)
	{
		CMarkup xml(childContent);
		xml.FindElem();
		_ID		= atoi(xml.GetAttrib("Id").c_str());
		_Type	= atoi(xml.GetAttrib("Type").c_str());
		_X		= atoi(xml.GetAttrib("X").c_str());
		_Y		= atoi(xml.GetAttrib("Y").c_str());
	}
	int GetID();
	int GetX();
	int GetY();
	int GetType();
};
//class Background
//{
//	CSpriteDx9*		m_tileSet;
//	int				m_Height;
//	int				m_Height;
//	int				m_Row;
//	int				m_Column;
//	int**			m_TileMap;
//	list<GameObject *> _ListGameObjects;
//public:
//	Background();
//	void Initialize(string filePath);
//	void Render(LPD3DXSPRITE spriteHandle);
//	void Release();
//	~Background();
//};
//
#endif