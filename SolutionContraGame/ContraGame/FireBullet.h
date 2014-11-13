#ifndef __FIREBULLET_H__
#define __FIREBULLET_H__

#include "Bullet.h"
#define COS_40 0.77
#define SIN_40 0.64

class FireBullet : public Bullet
{
private:
	D3DXVECTOR2 m_VelocityOfOrigin;
	D3DXVECTOR3 m_PositionOfOrigin;
	double m_Angle;
public:
	void setVelocityOrigin(D3DXVECTOR2 _VelocityOfOrigin){ this->m_VelocityOfOrigin = _VelocityOfOrigin ;};
	void setPositionOfOrigin(D3DXVECTOR3 _PositionOfOrigin){ this->m_PositionOfOrigin = _PositionOfOrigin;};
	void reset();
	FireBullet();
	FireBullet(D3DXVECTOR3, eDirection, eObjectID);
	void Initialize();
	void UpdateMovement();
	~FireBullet();
};

#endif