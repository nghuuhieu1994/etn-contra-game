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
	case eObjectID::BOOM:
	case eObjectID::TANK:
	case eObjectID::SNIPPER_WATER_HIDING:
	case eObjectID::MAGIC_ROCK:
	case eObjectID::STONE:
		return true;
	default:
		return false;
	}
	return false;
}

float Distance(Object* a, Object* b)
{
	float dx = abs(a->getPositionVec2().x - b->getPositionVec2().x);
	float dy = abs(a->getPositionVec2().y - b->getPositionVec2().y);

	return sqrtf(dx * dx + dy * dy);
}