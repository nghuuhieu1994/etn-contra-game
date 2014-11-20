#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

class CGlobal
{
public:
	static bool IsExit;
	static bool IsMute;
	static bool IsWindowMode;
	static int	Rambo_X;
	static int	Rambo_Y;
};

bool IsMovementObject(int type);

#endif