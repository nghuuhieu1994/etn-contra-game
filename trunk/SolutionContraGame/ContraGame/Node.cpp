#include "Node.h"


Node::Node()
{

}

Node::Node(int _ID, RECT _bound)
{
	this->mID = _ID;
	this->mBound = _bound;
	this->mTl = NULL;
	this->mTr = NULL;
	this->mBl = NULL;
	this->mBr = NULL;
}


Node::~Node()
{

}
