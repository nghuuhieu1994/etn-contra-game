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
	case eObjectID::SNIPER_STANDING:
	case eObjectID::WEAPON_CAPSULE:
		return true;
	default:
		return false;
	}
	return false;
}