#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#include "EObjectID.h"
#include "CObjectDx9.h"

class CGlobal
{
public:
	static bool IsExit;
	static bool IsMute;
	static bool IsWindowMode;
	static int	Rambo_X;
	static int	Rambo_Y;
	static int	MapName;
	static bool LiveOfRambo;
};

bool IsMovementObject(eObjectID type);
float Distance(Object*, Object*);

#endif