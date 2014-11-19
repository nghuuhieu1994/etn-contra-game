#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Node.h"
#include "Collision.h"
#include "Markup.h"
#include <list>
#include <vector>

class QuadTree
{
private:
	RECT mBoundWorld;
	bool mIsFirstLoadXml;
public:
	//std::list<Object*> mListObjectInView;
	std::vector<Object*> mListObjectInView;
	Node* mRootNode;
	Node* getRootNode() const { return this->mRootNode; };
	//std::list<Object*> getListObjectInView() const { return this->mListObjectInView; };
	RECT getBoundWorld() const { return this->mBoundWorld; };
	QuadTree();
	void InsertObjectIntoView(RECT, Node*);
	void BuildQuadtree(const char* content, Node*& node);
	~QuadTree();
};

#endif