
#include "Tank.h"

int arrMap[MAP_HEIGH][MAP_WIDTH] = {
						{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, //i ko đổi
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, //i ko đổi
						{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, //i ko đổi
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, //i ko đổi
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
						{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
					};



//update tăng
//chỉ có update bullet thôi
void UpdateTank(GTank &tank)
{
	if(tank.bullet.isLive == true)
	{
		if(tank.bullet.direction == GDirections::RIGHT)
		{
			tank.bullet.x += BULLET_VELLOC;
		}
		else
		if(tank.bullet.direction == GDirections::LEFT)
		{
			tank.bullet.x -= BULLET_VELLOC;
		}
		else
		if(tank.bullet.direction == GDirections::UP)
		{
			tank.bullet.y -= BULLET_VELLOC;
		}
		else
		if(tank.bullet.direction == GDirections::DOWN)
		{
			tank.bullet.y += BULLET_VELLOC;	
		}

		
		if(tank.bullet.x > MAP_LEFT + MAP_WIDTH || tank.bullet.x < 0 || tank.bullet.y > MAP_TOP + MAP_HEIGH || tank.bullet.y < 0)
		{
			tank.bullet.isLive = false;
		}
	}
}


bool canMoveRight(GTank tank)
{
	GPoint2D pos1InMap = {tank.x + 1 - MAP_LEFT, tank.y - 1 - MAP_TOP}; //top-right
	GPoint2D pos2InMap = {tank.x + 2 - MAP_LEFT, tank.y     - MAP_TOP};	//middler-right
	GPoint2D pos3InMap = {tank.x + 1 - MAP_LEFT, tank.y + 1 - MAP_TOP}; //bottom-right

	//gặp tường
	if(arrMap[pos1InMap.y][pos1InMap.x] != 0 ||
		arrMap[pos2InMap.y][pos2InMap.x] != 0 ||
		arrMap[pos3InMap.y][pos3InMap.x] != 0)
	{
		return false;
	}

	//ra ngoài map
	if(tank.x >= MAP_WIDTH + MAP_LEFT - 3)
	{
		return false;
	}
	
	return true;
}

bool canMoveLeft(GTank tank)
{
	GPoint2D pos1InMap = {tank.x - 1 - MAP_LEFT, tank.y - 1 - MAP_TOP}; //top-LEFT
	GPoint2D pos2InMap = {tank.x - 2 - MAP_LEFT, tank.y     - MAP_TOP};	//middler-LEFT
	GPoint2D pos3InMap = {tank.x - 1 - MAP_LEFT, tank.y + 1 - MAP_TOP}; //bottom-LEFT

	//gặp tường
	if(arrMap[pos1InMap.y][pos1InMap.x] != 0 ||
		arrMap[pos2InMap.y][pos2InMap.x] != 0 ||
		arrMap[pos3InMap.y][pos3InMap.x] != 0)
	{
		return false;
	}
	
	//ra ngoài map
	if(tank.x <= MAP_LEFT + 2)
	{
		return false;
	}
	
	return true;
}

bool canMoveUp(GTank tank)
{
	GPoint2D pos1InMap = {tank.x - 1 - MAP_LEFT, tank.y - 1 - MAP_TOP}; //LEFT-top
	GPoint2D pos2InMap = {tank.x     - MAP_LEFT, tank.y - 2 - MAP_TOP};	//LEFT-middler
	GPoint2D pos3InMap = {tank.x + 1 - MAP_LEFT, tank.y - 1 - MAP_TOP}; //LEFT-bottom

	//gặp tường
	if(arrMap[pos1InMap.y][pos1InMap.x] != 0 ||
		arrMap[pos2InMap.y][pos2InMap.x] != 0 ||
		arrMap[pos3InMap.y][pos3InMap.x] != 0)
	{
		return false;
	}
	
	//ra ngoài map
	if(tank.y <= MAP_TOP + 3)
	{
		return false;
	}
	
	return true;
}

bool canMoveDown(GTank tank)
{
	GPoint2D pos1InMap = {tank.x - 1 - MAP_LEFT, tank.y + 1 - MAP_TOP}; //LEFT-bottom
	GPoint2D pos2InMap = {tank.x     - MAP_LEFT, tank.y + 2 - MAP_TOP};	//middle-bottom
	GPoint2D pos3InMap = {tank.x + 1 - MAP_LEFT, tank.y + 1 - MAP_TOP}; //RIGHT-bottom

	//gặp tường
	if(arrMap[pos1InMap.y][pos1InMap.x] != 0 ||
		arrMap[pos2InMap.y][pos2InMap.x] != 0 ||
		arrMap[pos3InMap.y][pos3InMap.x] != 0)
	{
		return false;
	}
	
	//ra ngoài map
	if(tank.y >= MAP_TOP + MAP_WIDTH - 3)
	{
		return false;
	}
	
	return true;
}


void DrawTank(GTank tank)
{
	/*************
	 @
	@@@
	@ @
	*************/
	int x = tank.x;
	int y = tank.y;

	if(tank.direction == GDirections::UP)
	{
		GPutCharToBuffer('@', x, y, tank.bodyColor);
		GPutCharToBuffer('@', x-1, y, tank.bodyColor); //left
		GPutCharToBuffer('@', x-1, y+1, tank.bodyColor);
		GPutCharToBuffer('@', x+1, y, tank.bodyColor); //right
		GPutCharToBuffer('@', x+1, y+1, tank.bodyColor);
		
		//header
		GPutCharToBuffer('@', x, y-1, tank.headerColor);
	}
	else if(tank.direction == GDirections::DOWN)
	{
		GPutCharToBuffer('@', x, y, tank.bodyColor);
		GPutCharToBuffer('@', x-1, y, tank.bodyColor); //left
		GPutCharToBuffer('@', x-1, y-1, tank.bodyColor);
		GPutCharToBuffer('@', x+1, y, tank.bodyColor); //right
		GPutCharToBuffer('@', x+1, y-1, tank.bodyColor);
		
		//header
		GPutCharToBuffer('@', x, y+1, tank.headerColor);
	} 
	else if(tank.direction == GDirections::LEFT)
	{
		GPutCharToBuffer('@', x, y, tank.bodyColor);
		GPutCharToBuffer('@', x, y-1, tank.bodyColor); //top
		GPutCharToBuffer('@', x+1, y-1, tank.bodyColor);
		GPutCharToBuffer('@', x, y+1, tank.bodyColor); //bottom
		GPutCharToBuffer('@', x+1, y+1, tank.bodyColor);
		
		//header
		GPutCharToBuffer('@', x-1, y, tank.headerColor);
	} 
	else if(tank.direction == GDirections::RIGHT)
	{
		GPutCharToBuffer('@', x, y, tank.bodyColor);
		GPutCharToBuffer('@', x, y-1, tank.bodyColor); //top
		GPutCharToBuffer('@', x-1, y-1, tank.bodyColor);
		GPutCharToBuffer('@', x, y+1, tank.bodyColor); //bottom
		GPutCharToBuffer('@', x-1, y+1, tank.bodyColor);
		
		//header
		GPutCharToBuffer('@', x+1, y, tank.headerColor);
	}

	////////////////////////////////////////
	//draw bullet
	if(tank.bullet.isLive == true)
	{
		GPutCharToBuffer('+', tank.bullet.x, tank.bullet.y, tank.headerColor);
	}
}


void DrawMap(int arr[MAP_HEIGH][MAP_WIDTH], int top, int left)
{
	for (int i = 0; i < MAP_HEIGH; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if(arr[i][j] != 0)
			{
				GPutCharToBuffer('O', j + left, i + top);
			}
		}
	}
}


