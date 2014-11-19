#ifndef __MAPQUADTREE_H__
#define __MAPQUADTREE_H__

#include "Node.h"
#include "CObjectDx9.h"
#include <map>

class MapQuadtree
{
private:
	std::map<int, Node*> mMapQuadtree;
	std::map<int, Object*> mMapObject;
	int mMapWidth;
	int mMapHeight;
public:
	std::map<int, Node*> getMapQuadtree() const { return this->mMapQuadtree; };
	std::map<int, Object*> getMapObject() const { return this->mMapObject; };
	MapQuadtree(const char* pathFileName);
	~MapQuadtree();
};

#endif