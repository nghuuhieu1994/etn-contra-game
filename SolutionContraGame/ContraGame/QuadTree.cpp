#include "QuadTree.h"


QuadTree::QuadTree()
{
	this->mRootNode = NULL;
	this->mIsFirstLoadXml = true;
}

void QuadTree::InsertObjectIntoView(RECT viewPort, Node* node)
{
	int j = 0;

	if (node == this->mRootNode)
	{
		if (this->mListObjectInView.size() > 0 && this->mListObjectCollisionInView.size() > 0)
		{
			this->mListObjectInView.clear();
			this->mListObjectCollisionInView.clear();
		}
	}

	if (CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getBound())))
	{
		for(int i = 0; i < (int)node->mListObject.size(); ++i)
		{
			mListObjectInView.push_back(node->mListObject[i]);
		}

		for(int i = 0; i < (int)node->mListObjectCollision.size(); ++i)
		{
			if(mMapObjectCollisionInGame[node->mListObjectCollision[i]]->getObjectState() != eObjectState::STATE_DEATH && mMapObjectCollisionInGame[node->mListObjectCollision[i]]->getObjectState() != eObjectState::STATE_BOSS_DEATH)
			{
				for( j = 0; j < (int)mListObjectCollisionInView.size(); ++j)
				{
					if(node->mListObjectCollision[i] == mListObjectCollisionInView[j])
						break;
				}

				if(j == mListObjectCollisionInView.size())
				{
					
					mListObjectCollisionInView.push_back(node->mListObjectCollision[i]);
				}
			}
			else
			{
				//mMapObjectCollisionInGame[node->mListObjectCollision[i]]->Release();
				node->mListObjectCollision.erase(node->mListObjectCollision.begin() + i);
			}
		}

		if (node->getBl() != NULL)
			InsertObjectIntoView(viewPort, node->getBl());
		if (node->getBr() != NULL)
			InsertObjectIntoView(viewPort, node->getBr());
		if (node->getTl() != NULL)
			InsertObjectIntoView(viewPort, node->getTl());
		if (node->getTr() != NULL)
			InsertObjectIntoView(viewPort, node->getTr());
	}
}

void QuadTree::Release(Node* node)
{
	if(node->getBl() != NULL)
	{
		// de quy
		Release(node->getBl());
		Release(node->getBr());
		Release(node->getTl());
		Release(node->getTr());
	}
	else // neu khong con node con, thi tien hanh release cac object
	{
		node->mListObjectCollision.clear();
		node->mListObjectCollision.clear();
		delete node;
		node = NULL;
	}
}

void QuadTree::BuildQuadtree(const char* content, Node*& node, eSpriteID _tile_map)
{
	if(this->mIsFirstLoadXml == true)
	{
		CMarkup xml;
		xml.Load(content);
		xml.FindElem("Map");
		xml.IntoElem();
		xml.FindElem("Node");
		xml.FindElem();
		if(node == NULL)
		{
			RECT bound = RECT();
			bound.left = atoi(xml.GetAttrib("X").c_str());
			bound.top = atoi(xml.GetAttrib("Y").c_str());
			bound.bottom = bound.top - atoi(xml.GetAttrib("Height").c_str());
			bound.right = bound.left + atoi(xml.GetAttrib("Width").c_str());
			node = new Node(atoi(xml.GetAttrib("Id").c_str()), bound);
		}
		this->mIsFirstLoadXml = false;
		xml.IntoElem();
		if(xml.FindElem("Node"))
		{
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTr, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBr, _tile_map);
		}
	}
	else
	{
		CMarkup xml(content);
		xml.FindElem("Node");
		xml.FindElem();
		RECT bound = RECT();
		bound.left = atoi(xml.GetAttrib("X").c_str());
		bound.top = atoi(xml.GetAttrib("Y").c_str());
		bound.bottom = bound.top - atoi(xml.GetAttrib("Height").c_str());
		bound.right = bound.left + atoi(xml.GetAttrib("Width").c_str());
		node = new Node(atoi(xml.GetAttrib("Id").c_str()), bound);
		
		xml.IntoElem();
		if(xml.FindElem("Node"))
		{
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTr, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBr, _tile_map);
		}
		else
		{
			if(xml.FindElem("Objects"))
			{
				xml.IntoElem();
				std::map<int, Object*>::iterator i;
				while(xml.FindElem("Object"))
				{
					i = mMapObjectInGame.find(atoi(xml.GetAttrib("Index").c_str()));
					if(i == mMapObjectInGame.end())
					{
						if(atoi(xml.GetAttrib("Type").c_str()) == 0)
						{
							mMapObjectInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tile(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f), atoi(xml.GetAttrib("Id").c_str()),
								_tile_map);
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 1)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new VirtualObject(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								atoi(xml.GetAttrib("Width").c_str()), 
								atoi(xml.GetAttrib("Height").c_str()),
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::GUN_ROTATING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new GunRotating(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::SNIPER_STANDING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new SniperStanding(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								0.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BRIDGE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  Bridge(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f), 
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_RUN)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  EnemyRun(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::SNIPER_HIDING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  SniperHiding(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BIG_GUN_ROTATING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigGunRotating(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::WEAPON_CAPSULE)
						{
							int tempIndex = atoi(xml.GetAttrib("Index").c_str());
							float tempPositionX = (float)(atoi(xml.GetAttrib("X").c_str()));
							float tempPositionY = (float)(atoi(xml.GetAttrib("Y").c_str()));
							int tempId = atoi(xml.GetAttrib("Id").c_str());
							xml.FindElem("Object");
							int temp = atoi(xml.GetAttrib("Id").c_str());
							mMapObjectCollisionInGame[tempIndex] = new WeaponCapsule(D3DXVECTOR3(
								tempPositionX,
								tempPositionY,
								1.0f),
								eDirection::LEFT,
								(eObjectID)tempId,
								(eObjectID)temp);
							mMapObjectCollisionInGame[tempIndex]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::WEAPON_SENSOR)
						{
							int tempIndex = atoi(xml.GetAttrib("Index").c_str());
							float tempPositionX = (float)(atoi(xml.GetAttrib("X").c_str()));
							float tempPositionY = (float)(atoi(xml.GetAttrib("Y").c_str()));
							int tempId = atoi(xml.GetAttrib("Id").c_str());
							xml.FindElem("Object");
							int temp = atoi(xml.GetAttrib("Id").c_str());
							mMapObjectCollisionInGame[tempIndex] = new WeaponSensor(D3DXVECTOR3(
								tempPositionX,
								tempPositionY,
								1.0f),
								eDirection::LEFT,
								(eObjectID)tempId,
								(eObjectID)temp);
							mMapObjectCollisionInGame[tempIndex]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BIG_GUN_ROTATING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigGunRotating(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BIG_BOSS_1)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tinker(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::SNIPPER_WATER_HIDING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new SnipperWaterHiding(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::TANK)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tank(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::MAGIC_ROCK)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BridgeStone(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::STONE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigStone(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BOOM)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Boom(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BIG_CAPSULE_BOSS)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigCapsuleBoss(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::FIRE_BRIDGE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new FireBridge(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_RUN_SHOOTING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemyRunShooting(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), eDirection::LEFT, (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
					}

					if(atoi(xml.GetAttrib("Type").c_str()) == (int)ETypeObject::TILE_MAP)
					{
						node->mListObject.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
					else if(atoi(xml.GetAttrib("Type").c_str()) == (int)ETypeObject::VIRTUAL_OBJECT || atoi(xml.GetAttrib("Type").c_str()) == (int)ETypeObject::DYNAMIC_OBJECT)
					{
						if(atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_BARRIER
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_FLAME_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_LASER_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_MACHINE_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_RAPID_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_SPREAD_GUN)
						node->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()) - 1);
						else
						node->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
				}
			}
		}
	}
}

void QuadTree::Update()
{
	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->Update();
	}
}

void QuadTree::UpdateAnimation()
{
	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->UpdateAnimation();
	}
}

void QuadTree::UpdateCollision(Object* checkingObject)
{
	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->UpdateCollision(checkingObject);
	}
}

void QuadTree::UpdateMovement()
{	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		if(IsMovementObject(mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->getID()))
		{
			DynamicObject* tempObject = (DynamicObject*)mMapObjectCollisionInGame[mListObjectCollisionInView[i]];
			tempObject->UpdateMovement();
		}
	}
}

void QuadTree::Render(SPRITEHANDLE spriteHandler)
{
	for(int i = 0; i < (int)mListObjectInView.size(); ++i)
	{
		mMapObjectInGame[mListObjectInView[i]]->Render(spriteHandler);
	}

	for(int j = 0; j < (int)mListObjectCollisionInView.size(); ++j)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[j]]->Render(spriteHandler);
	}
}

QuadTree::~QuadTree()
{

}
