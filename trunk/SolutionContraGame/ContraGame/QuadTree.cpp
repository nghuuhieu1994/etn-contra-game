#include "QuadTree.h"


QuadTree::QuadTree()
{
	this->mRootNode = NULL;
	this->mIsFirstLoadXml = true;
}

void QuadTree::InsertObjectIntoView(RECT viewPort, Node* node)
{
	int j = 0;

	if(node == this->mRootNode)
	{
		if(this->mListObjectInView.size() > 0)
			this->mListObjectInView.clear();
	}

	if(node->getBl() == NULL)
	{
		if(CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getBound())))
		{
			
			for(int i = 0; i < node->mListObject.size(); ++i)
			{
				mListObjectInView.push_back(node->mListObject[i]);
			}

			//for(std::list<Object*>::iterator i = node->mListObject.begin(); i != node->mListObject.end(); ++i)
			//{
			//	//for(j = 0; j < mVectorListObjectInView.size(); ++j)
			//	//{
			//	//	if((*i) == mVectorListObjectInView[j])
			//	//	{
			//	//		break;
			//	//	}
			//	//}

			//	//if(j == mVectorListObjectInView.size())
			//	//{
			//		mListObjectInView.push_back(*i);
			//	//	mVectorListObjectInView.push_back(*i);
			//	//}
			//}
		}
	}
	else
	{
		if(Intersect(viewPort, node->getBl()->getBound()))
		{
			InsertObjectIntoView(viewPort, node->getBl());
		}

		if(Intersect(viewPort, node->getBr()->getBound()))
		{
			InsertObjectIntoView(viewPort, node->getBr());
		}

		if(Intersect(viewPort, node->getTl()->getBound()))
		{
			InsertObjectIntoView(viewPort, node->getTl());
		}

		if(Intersect(viewPort, node->getTr()->getBound()))
		{
			InsertObjectIntoView(viewPort, node->getTr());
		}
	}
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
				while(xml.FindElem("Object"))
				{
					//xml.FindElem();
					if(atoi(xml.GetAttrib("Type").c_str()) == 0)
					{
						// new tile object
						node->mListObject.push_back(new Tile(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
							atoi(xml.GetAttrib("Y").c_str()), 1.0f), atoi(xml.GetAttrib("Id").c_str()),
							eSpriteID::SPRITE_MAP_1));
					}
					else if(atoi(xml.GetAttrib("Type").c_str()) == 1)
					{
						node->mListObject.push_back(new VirtualObject(D3DXVECTOR3(atoi(xml.GetAttrib("X").c_str()),
							atoi(xml.GetAttrib("Y").c_str()), 1.0f), atoi(xml.GetAttrib("Width").c_str()), 
							atoi(xml.GetAttrib("Height").c_str()), (eObjectID)atoi(xml.GetAttrib("Id").c_str())));
					}
				}
			}
		}
	}
}

QuadTree::~QuadTree()
{

}
