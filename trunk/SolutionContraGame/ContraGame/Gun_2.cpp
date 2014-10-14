//#include "Gun_2.h"
//
//Gun_2::Gun_2()
//{}
//Gun_2::Gun_2(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
//	: Object(_position, _direction, _objectID)
//{
//
//}
//
//void Gun_2::Initialize()
//{
//	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
//	m_Direction = eDirection::LEFT;
//	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_2));
//}
//
//void Gun_2::UpdateMovement()
//{
//}
//
//void Gun_2::UpdateCollision(Object* checkingObject)
//{
//}
//
//void Gun_2::UpdateAnimation()
//{
//	switch (m_ObjectState)
//	{
//	case STATE_ALIVE_IDLE:
//		int _distance = abs(CGlobal::Rambo_X - m_Physic->getPositionVec2().x);
//		if(_distance > 400)
//		{
//			m_Sprite->getAnimation()->setIndexStart(0);
//			m_Sprite->getAnimation()->setIndexEnd(1);
//			m_Sprite->UpdateAnimation(150);
//		}
//		else
//		{
//
//		}
//		
//		break;
//	case STATE_SHOOTING:
//		break;
//	case STATE_BEFORE_DEATH:
//		break;
//	case STATE_DEATH:
//		break;
//	default:
//		break;
//	}
//}
//
//void Gun_2::Update()
//{
//}
//
//void Gun_2::Render(SPRITEHANDLE spriteHandle)
//{
//	m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
//}
//
//void Gun_2::Release()
//{
//	m_Sprite->Release();
//}
//Gun_2::~Gun_2()
//{
//}