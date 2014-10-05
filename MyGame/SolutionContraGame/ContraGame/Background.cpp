#include "Background.h"
#include <fstream>
#include "SpriteManager.h"

Background::Background()
{

}

void Background::Initialize(string filePath)
{
	fstream file(filePath.c_str(), ios::in | ios::app);

	file >> m_Width;
	file >> m_Height;
	file >> m_Row;
	file >> m_Column;
	
	m_TileMap = new int*[m_Row];

	for (int i = 0; i < m_Row; i++)
	{
		m_TileMap[i] = new int[m_Column]();
	}

	for (int i = 0; i < m_Row; i++)
	{
		for (int j = 0; j < m_Column; j++)
		{
			file >> m_TileMap[i][j];
		}
	}

	file.close();
}

void Background::Release()
{
	
	for (int i = 0; i < m_Row; i++)
	{
		delete[] m_TileMap[i];
		m_TileMap[i] = 0;
	}
	delete m_TileMap;
	m_TileMap = 0;
}

void Background::Render(LPD3DXSPRITE spriteHandle)
{
	for (int i = 0; i < m_Row; i++)
	{
		for (int j = 0; j < m_Column; j++)
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::MAP_1)->RenderAtFrame(spriteHandle, D3DXVECTOR2(TILE_WIDTH/2 + j * TILE_WIDTH, m_Height - TILE_HEIGHT/2 - i * TILE_HEIGHT), eSpriteEffect::None, 0.0f, 1.0f, 1.0f, 0xffffffff, m_TileMap[i][j]);
		}
	}
}

Background::~Background()
{

}