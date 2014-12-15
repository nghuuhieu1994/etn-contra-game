#ifndef __NODE_H__
#define __NODE_H__

#include "CObjectDx9.h"
#include <list>
#include <vector>
#include "Collision.h"
#include "Tile.h"
#include "VirtualObject.h"
#include "BackgroundEffect.h"
#include "GunRotating.h"
#include "SniperStanding.h"
#include "Bridge.h"
#include "EnemyRun.h"
#include "SniperHiding.h"
#include "BigGunRotating.h"
#include "WeaponCapsule.h"
#include "WeaponSensor.h"
#include "Tinker.h"
#include "SnipperWaterHiding.h"
#include "Tank.h"
#include "BridgeStone.h"
#include "BigStone.h"
#include "Boom.h"
#include "BigCapsuleBoss.h"
#include "FireBridge.h"
#include "EnemyRunShooting.h"
#include "RoShan.h"

class Node
{
private:
	 int mID;
	 RECT mBound;
public:
	Node* mTl;
	Node* mTr;
	Node* mBl;
	Node* mBr;
	std::vector<int> mListObject;
	std::vector<int> mListObjectCollision;

	int getID() const { return this->mID; };
	RECT getBound() const { return this->mBound; };
	std::vector<int> getListObject() const { return this->mListObject; };
	std::vector<int> getListObjectCollision() const { return this->mListObjectCollision; };

	Node* getTl() const { return this->mTl; };
	Node* getTr() const { return this->mTr; };
	Node* getBl() const { return this->mBl; };
	Node* getBr() const { return this->mBr; };

	void setTl(Node* _tl) { this->mTl = _tl;};
	Node();
	Node(int, RECT);
	~Node();
};

#endif