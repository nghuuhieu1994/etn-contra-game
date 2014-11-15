#include "Tinker.h"

Tinker::Tinker(){}

Tinker::Tinker(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
}

void Tinker::Initialize()
{
	this->m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	this->m_Body = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY);
	
	m_Sprite = m_Body;

	m_Center = new BossCenter(D3DXVECTOR3(this->getPositionVec3().x - 80, this->getPositionVec3().y - 80, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_CENTER);
	m_Center->Initialize();
	m_Left = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 50, this->getPositionVec3().y - 50, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Left->Initialize();
	m_Right = new BossGun(D3DXVECTOR3(this->getPositionVec3().x + 50, this->getPositionVec3().y + 50, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Right->Initialize();
}

void Tinker::UpdateAnimation()
{
	m_Left->UpdateAnimation();
	m_Right->UpdateAnimation();
	m_Center->UpdateAnimation();
}

void Tinker::UpdateCollision(Object* checkingObject)
{
	m_Left->UpdateCollision(checkingObject);
	m_Right->UpdateCollision(checkingObject);
	m_Center->UpdateCollision(checkingObject);
}

void Tinker::UpdateMovement(){}

void Tinker::Update()
{

}

void Tinker::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);
	}
	m_Left->Render(spriteHandle);
	m_Right->Render(spriteHandle);
	m_Center->Render(spriteHandle);
}

void Tinker::Release()
{}

Tinker::~Tinker()
{}