#ifndef __MapReader_h__
#define __MapReader_h__
#include "Markup.h"
#include <list>
#include "CObjectDx9.h"
using namespace std;

class GameObjectXML
{
private:
	int m_ID;
	int m_X;
	int m_Y;
	int m_Type;
	int m_Width;
	int m_Height;
public:
	void Deserialize(const char *childContent);
	void DeserializeVirtualObject(const char* childContent);
	void DeserializeTile(const char *childContent);
	int GetID();
	int GetX();
	int GetY();
	int GetType();
	int GetWidth();
	int GetHeight();
};

class MapReader
{
private:
	static MapReader* s_Instance;
	MapReader(){}
	~MapReader(){}
public:
	static MapReader* getInstance();
	void ReadMap(const char* _filePath, list<Object*>* _listObject, list<Object*>* _backgroundList);
};

#endif