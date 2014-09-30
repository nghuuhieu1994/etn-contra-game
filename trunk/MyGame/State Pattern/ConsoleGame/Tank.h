
#ifndef __TANK_H__
#define __TANK_H__
#pragma once

#include "Utils.h"


#define BULLET_VELLOC	0.75f
#define TANK_VELLOC		0.75f

#define MAP_WIDTH	40
#define MAP_HEIGH	40

#define MAP_TOP		0 //top of map in screen
#define MAP_LEFT	0 //left of map in screen


//viên đạn
typedef struct GBullet
{
	float x; //in screen
	float y;
	bool isLive;
	GDirections direction;
} GBullet;


//xe tăng
typedef struct GTank 
{
	float x; //in screen
	float y;
	
	GDirections direction;
	GColors headerColor;
	GColors bodyColor;

	GBullet bullet;
} GTank;


extern int arrMap[MAP_HEIGH][MAP_WIDTH];



//update tăng
//chỉ có update bullet thôi
void UpdateTank(GTank &tank);

bool canMoveRight(GTank tank);

bool canMoveLeft(GTank tank);

bool canMoveUp(GTank tank);

bool canMoveDown(GTank tank);

void DrawTank(GTank tank);

void DrawMap(int arr[MAP_HEIGH][MAP_WIDTH], int top, int left);



#endif //__TANK_H__

