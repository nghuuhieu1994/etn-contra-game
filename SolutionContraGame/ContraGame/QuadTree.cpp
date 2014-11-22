#include "QuadTree.h"


QuadTree::QuadTree()
{
	this->mRootNode = NULL;
	this->mIsFirstLoadXml = true;
}

void QuadTree::InsertObjectIntoView(RECT viewPort, Node* node)
{
	int j = 0;

	std::map<int, int> traceObject;

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
		std::map<int, int>::iterator iMap;
		for(int i = 0; i < node->mListObject.size(); ++i)
		{
			iMap = traceObject.find(node->mListObject[i]);
			if(iMap == traceObject.end())
			{
			//if(j == 100)
			//{
				mListObjectInView.push_back(node->mListObject[i]);
				traceObject[node->mListObject[i]] = 1;
			//}
			}
		}

		for(int i = 0; i < node->mListObjectCollision.size(); ++i)
			mListObjectCollisionInView.push_back(node->mListObjectCollision[i]);

		if (node->getBl() != NULL)
			InsertObjectIntoView(viewPort, node->getBl());
		if (node->getBr() != NULL)
			InsertObjectIntoView(viewPort, node->getBr());
		if (node->getTl() != NULL)
			InsertObjectIntoView(viewPort, node->getTl());
		if (node->getTr() != NULL)
			InsertObjectIntoView(viewPort, node->getTr());
	}
	/*int i = 0;
	int j = 0;

	if(node == this->mRootNode)
	{
		if(this->mListObjectInView.size() > 0 && this->mListObjectCollisionInView.size() > 0)
		{
			this->mListObjectInView.clear();
			this->mListObjectCollisionInView.clear();
		}
	}

	if(node->getBl() == NULL)
	{
		if(CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getBound())))
		{
			mListObjectInView.insert(node->mListObject.begin(), node->mListObject.end());
			mListObjectCollisionInView.insert(node->mListObjectCollision.begin(), node->mListObjectCollision.end());
		}
	}
	else
	{
		if(CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getBl()->getBound())))
		{
			InsertObjectIntoView(viewPort, node->getBl());
		}

		if(CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getBr()->getBound())))
		{
			InsertObjectIntoView(viewPort, node->getBr());
		}

		if(CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getTl()->getBound())))
		{
			InsertObjectIntoView(viewPort, node->getTl());
		}

		if(CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getTr()->getBound())))
		{
			InsertObjectIntoView(viewPort, node->getTr());
		}
	}*/
}


void QuadTree::PreBuilding(const char* content)
{
	CMarkup xml;
	xml.Load(content);
	std::map<int, Object*>::iterator i;
}

void QuadTree::BuildQuadtree(const char* content, Node*& node)
{
	if(this->mIsFirstLoadXml == true)
	{
		CMarkup xml;
		xml.Load(content);
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
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTl);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTr);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBl);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBr);
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
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTl);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTr);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBl);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBr);
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
							mMapObjectInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tile(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), atoi(xml.GetAttrib("Id").c_str()),
									eSpriteID::SPRITE_MAP_1);
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 1)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new VirtualObject(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
								atoi(xml.GetAttrib("Y").c_str()), 1.0f), atoi(xml.GetAttrib("Width").c_str()), 
									atoi(xml.GetAttrib("Height").c_str()), (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
						}
						//else if(atoi(xml.GetAttrib("Type").c_str()) == 2)
						//{
						//	mMapObjectInGame[atoi(xml.GetAttrib("Index").c_str())] = new LedObject(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
						//		atoi(xml.GetAttrib("Y").c_str()), 0.0f), (eObjectID)atoi(xml.GetAttrib("Id").c_str()));
						//}
					}

					if(atoi(xml.GetAttrib("Type").c_str()) == 0)
					{
						node->mListObject.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
					else if(atoi(xml.GetAttrib("Type").c_str()) == 1)
					{
						node->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
				}
			}
		}
	}
}

void QuadTree::Update()
{
	//for(int i = 0; i < mListObjectInView.size(); ++i)
	//{
	//	mListObjectInView[i]->Update();
	//}
}

void QuadTree::UpdateAnimation()
{
	//for(int i = 0; i < mListObjectInView.size(); ++i)
	//{
	//	mListObjectInView[i]->UpdateAnimation();
	//}
}

void QuadTree::UpdateCollision(Object* checkingObject)
{
	//for(int i = 0; i < mListObjectInView.size(); ++i)
	//{
	//	mListObjectInView[i]->UpdateCollision(checkingObject);
	//}
}

void QuadTree::Render(SPRITEHANDLE spriteHandler)
{
	for(int i = 0; i < mListObjectInView.size(); ++i)
	{
		mMapObjectInGame[mListObjectInView[i]]->Render(spriteHandler);
	}
}

QuadTree::~QuadTree()
{

}
