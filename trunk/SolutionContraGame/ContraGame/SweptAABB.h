#ifndef _SWEPTAABB_
#define _SWEPTAABB_

#include "d3d9.h"
#include "CGlobal.h"
#include <limits>

using namespace std;

// tạo một khoảng không gian chiếm bởi đối tượng với một vận tốc
static  BOX GetSweptBroadPhaseBox(BOX b)
{
	BOX broadphasebox(0, 0, 0, 0);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphasebox.y = b.vy > 0 ? b.y + b.vy : b.y;
	broadphasebox.width= b.vx > 0 ? b.vx + b.width : b.width - b.vx;
	broadphasebox.height = b.vy > 0 ? b.vy + b.height : b.height - b.vy;

	return broadphasebox;
}

// kiểm tra xem đối tượng có nằm trong vùng không gian bất kì
static bool CheckAABB(BOX box1, BOX box2)
{
	return !(box1.x + box1.width <= box2.x || box1.x >= box2.x + box2.width || box1.y - box1.height >= box2.y || box1.y <= box2.y - box2.height);
}

// kiểm tra vật có nằm ngoài vùng
// kiểm tra va chạm khi chưa có vận tốc
static bool AABB(BOX b1, BOX b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - ( b1.x + b1.width);
	float r = ( b2.x + b2.width) - b1.x;
	float t = ( b2.y - b2.height ) - b1.y;
	//float t = b2.y - (b1.y - b1.height);
	//float b = (b2.y - b2.height) - b1.y;
	float b = b2.y - ( b1.y - b1.height);

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return false;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

// thuật toán xét va chạm swept aabb
static float SweptAABB(BOX b1, BOX b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else 
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = (b2.y - b2.height) - b1.y;
		yInvExit = b2.y - (b1.y - b1.height);
	}
	else
	{
		yInvEntry = b2.y - (b1.y - b1.height);
		yInvExit = (b2.y - b2.height) - b1.y;
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{        		
		// calculate normal of collided surface
		if (xEntry > yEntry && (b1.y - b1.height != b2.y))
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry <= 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

#endif