#include "CGlobal.h"

bool CGlobal::IsWindowMode	= true;
bool CGlobal::IsExit		= false;
bool CGlobal::IsMute		= false;

int CGlobal::Rambo_X		= 0;
int CGlobal::Rambo_Y		= 0;

bool IsMovementObject(eObjectID id)
{
	switch(id)
	{
	case eObjectID::ENEMY_RUN:
		return true;
	default:
		return false;
	}
	return false;
}