#include "VectorDx9.h"

VectorDx9::VectorDx9()
{
	this->m_X = 0;
	this->m_Y = 0;
	this->m_Z = 0;
}

VectorDx9::VectorDx9(int x, int y)
{
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = 0;
}
VectorDx9::VectorDx9(int x, int y, int z)
{
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}
VectorDx9::VectorDx9(const VectorDx9 &vector)
{
	this->m_X = vector.m_X;
	this->m_Y = vector.m_Y;
	this->m_Z = vector.m_Z;
}
int VectorDx9::getX()
{
	return this->m_X;
}
int VectorDx9::getY()
{
	return this->m_Y;
}
int VectorDx9::getZ()
{
	return this->m_Z;
}
void VectorDx9::setX(int x)
{
	this->m_X = x;
}
void VectorDx9::setY(int y)
{
	this->m_Y = y;
}
void VectorDx9::setZ(int z)
{
	this->m_Z = z;
}

void VectorDx9::setZero()
{
	this->m_X = 0;
	this->m_Y = 0;
	this->m_Z = 0;
}

VectorDx9::~VectorDx9()
{
	this->m_X = 0;
	this->m_Y = 0;
	this->m_Z = 0;
}