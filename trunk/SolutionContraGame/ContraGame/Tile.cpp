#include "Tile.h"


Tile::Tile(void)
{
}

Tile::Tile(D3DXVECTOR3 _position, int ID, eSpriteID tileMapID)
{
	m_TypeObject = ETypeObject::TILE_MAP;
	m_Position = _position;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(tileMapID));
	m_Sprite->getAnimation()->setIndexStart(ID);
	m_Sprite->getAnimation()->setIndexEnd(ID);
}

void Tile::Initialize()
{

}
void Tile::UpdateAnimation()
{

}
void Tile::UpdateCollision(Object* checkingObject)
{
}

void Tile::Update()
{
}

void Tile::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2(), ESpriteEffect::None, 0.0f, 1.0f, getPositionVec3().z);
}

void Tile::Release()
{
}

Tile::~Tile(void)
{
}
