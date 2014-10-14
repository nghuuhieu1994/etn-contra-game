#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <d3d9.h>

class VectorDx9
{
private:
	// X element
	int		m_X;
	// Y element
	int		m_Y;
	// Z element
	int		m_Z;
public:
	// Constructor 0 parametor
	VectorDx9();
	// Constructor x,y parametor
	VectorDx9(int x, int y);
	// Constructor x,y,z parametor
	VectorDx9(int x, int y, int z);
	// Copi constructor
	VectorDx9(const VectorDx9 &vector);
	// get X element
	int getX();
	// get Y element
	int getY();
	// get Z element
	int getZ();
	// set a value to X element
	void setX(int x);
	// set a value to Y element
	void setY(int y);
	// set a value to Z element
	void setZ(int z);
	// Destroy VectorDx9
	void setZero();
	~VectorDx9();
};


#endif