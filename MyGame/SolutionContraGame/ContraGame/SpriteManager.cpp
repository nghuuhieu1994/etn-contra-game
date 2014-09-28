#include "SpriteManager.h"

SpriteManager* SpriteManager::s_Instance = 0;

SpriteManager::SpriteManager(void)
{
	Bill = 0;
}

SpriteManager* SpriteManager::GetInstance()
{
	if(s_Instance == 0)
	{
		s_Instance = new SpriteManager();
	}
	return s_Instance;
}

SpriteManager::~SpriteManager(void)
{
}
