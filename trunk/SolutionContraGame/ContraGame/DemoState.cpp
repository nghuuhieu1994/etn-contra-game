#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{

	m_UnitTest.x = 400;
	m_UnitTest.y = 300;
	m_UnitTest.z = 0;

	//m_background = new Background();
	//m_background->Initialize("resources\\Map\\1\\1.map");
	
	m_Rambo = new Rambo(D3DXVECTOR3(100, 449, 1), eDirection::RIGHT, eObjectID::RAMBO);
	m_SniperStanding = new SniperStanding(D3DXVECTOR3(650, 130, 0), eDirection::LEFT, eObjectID::SNIPER_STANDING);
	m_SniperStanding->Initialize();

	m_snipperHiding = new SniperHiding(D3DXVECTOR3(750, 290, 0), eDirection::LEFT, eObjectID::SNIPER_HIDING);
	m_snipperHiding->Initialize();

	m_gifBullet = new GifBulletStatic(D3DXVECTOR3(500, 200, 1), eDirection::LEFT, eObjectID::GIF_BULLET_STATIC);
	m_gifBullet->Initialize();

	m_gifBulletMoving = new GifBulletMoving(D3DXVECTOR3(30, 200, 1), eDirection::LEFT, eObjectID::GIF_BULLET_MOVING);
	m_gifBulletMoving->Initialize();

	m_gunRotating = new GunRotating(D3DXVECTOR3(600, 200, 1), eDirection::LEFT, eObjectID::GUN_ROTATING);
	m_gunRotating->Initialize();
	
	m_bigGunRotating = new BigGunRotating(D3DXVECTOR3(800, 10, 1), eDirection::LEFT, eObjectID::BIG_GUN_ROTATING);
	m_bigGunRotating->Initialize();

	m_Enemy = new EnemyRun(D3DXVECTOR3(500, 100, 1), eDirection::LEFT, eObjectID::ENEMY_RUN);
	m_Enemy->Initialize();

	/*m_VirtualObject = new VirtualObject(D3DXVECTOR3(96, 224, 1), 64, 64);
	m_VirtualObject->Initialize();*/

	//_ListGameObjects.push_back(m_VirtualObject);

	ReadMap();
}

void DemoState::ReadMap()
{
	CMarkup xml;
	xml.Load("resources\\Map\\1\\map.xml");
	xml.FindElem("Objects");
	xml.IntoElem();

	while (xml.FindElem("Object"))
	{
		GameObject *_GameObject;
		_GameObject = new GameObject();
		_GameObject->Deserialize(xml.GetSubDoc().c_str());
		//_ListGameObjects.push_back(_GameObject);
		/*if (_GameObject->_Type == ETypeObject::TILE_MAP)
		{
			_GameObject->DeserializeTile(xml.GetSubDoc().c_str());
			Object* temp = new Tile(D3DXVECTOR3(_GameObject->_X, _GameObject->_Y, 0), _GameObject->_ID, eSpriteID::SPRITE_MAP_1);
			_ListGameObjects.push_back(temp);
		}*/
		Object* temp = 0;
		switch (_GameObject->_Type)
		{
		case ETypeObject::TILE_MAP:
			{
				_GameObject->DeserializeTile(xml.GetSubDoc().c_str());
				temp = new Tile(D3DXVECTOR3(_GameObject->_X, _GameObject->_Y, 0), _GameObject->_ID, eSpriteID::SPRITE_MAP_1);
				m_backgroundTile.push_back(temp);
				temp = 0;
			}
			break;
		case ETypeObject::VIRTUAL_OBJECT:
			{
				_GameObject->DeserializeVirtualObject(xml.GetSubDoc().c_str());
				//temp = new Tile(D3DXVECTOR3(_GameObject->_X, _GameObject->_Y, 0), _GameObject->_ID, eSpriteID::SPRITE_MAP_1);
				temp = new VirtualObject(D3DXVECTOR3(_GameObject->_X, _GameObject->_Y, 1), _GameObject->m_Width, _GameObject->m_Height);
			}
			break;
		case ETypeObject::STATIC_OBJECT:
			{

			}
			break;
		case ETypeObject::DYNAMIC_OBJECT:
			{

			}
			break;
		default:
			break;
		}
		if (temp != 0)
		{
			_ListGameObjects.push_back(temp); 
		}
	}
}

void DemoState::HandleInput()
{
	m_Rambo->HandleInput();
}

void DemoState::Update()
{

	m_Rambo->UpdateAnimation();
	
	m_Rambo->UpdateMovement();

	for (std::list<Object*>::iterator it = _ListGameObjects.begin(); it != _ListGameObjects.end(); ++it)
	{
		if ((*it)->getTypeObject() != ETypeObject::TILE_MAP)
		{
			m_Rambo->UpdateCollision(*it); 
		}
	}
	
	Camera::getInstance()->UpdateCamera(&m_Rambo->getPositionVec3());

	m_SniperStanding->UpdateCollision(m_Rambo);
	m_SniperStanding->UpdateAnimation();
	m_SniperStanding->Update();

	m_gifBullet->UpdateCollision(m_Rambo);
	m_gifBullet->UpdateAnimation();
	m_gifBullet->Update();

	m_gunRotating->UpdateCollision(m_Rambo);
	m_gunRotating->UpdateAnimation();
	m_gunRotating->Update();

	m_bigGunRotating->UpdateCollision(m_Rambo);
	m_bigGunRotating->UpdateAnimation();
	m_bigGunRotating->Update();


	m_gifBulletMoving->UpdateCollision(m_Rambo);
	m_gifBulletMoving->UpdateAnimation();
	m_gifBulletMoving->UpdateMovement();

	m_snipperHiding->UpdateAnimation();
	m_snipperHiding->Update();
	m_snipperHiding->UpdateCollision(m_Rambo);
	
	m_Enemy->UpdateAnimation();
	m_Enemy->UpdateMovement();
}

void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	//m_background->Render(_lpDSpriteHandle);
	for (std::list<Object*>::iterator it = m_backgroundTile.begin(); it != m_backgroundTile.end(); it++)
	{
		(*it)->Render(_lpDSpriteHandle);
	}
	


	m_gifBullet->Render(_lpDSpriteHandle);
	m_gifBulletMoving->Render(_lpDSpriteHandle);
	m_SniperStanding->Render(_lpDSpriteHandle);
	m_gunRotating->Render(_lpDSpriteHandle);
	m_bigGunRotating->Render(_lpDSpriteHandle);
	m_Rambo->Render(_lpDSpriteHandle);
	
	m_Enemy->Render(_lpDSpriteHandle);
	m_snipperHiding->Render(_lpDSpriteHandle);
}

void DemoState::Pause()
{

}

void DemoState::Resume()
{

}

void DemoState::Release()
{
	for (std::list<Object*>::iterator it = _ListGameObjects.begin(); it != _ListGameObjects.end(); it++)
	{
		/*if ((*it)->_Type == 0)
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MAP_1)->RenderAtFrame(_lpDSpriteHandle, D3DXVECTOR2((float)(*it)->_X, (float)(*it)->_Y), ESpriteEffect::None, 0.0f, 1.0f, 0.0f, 0xffffffff, (*it)->_ID); 
		}*/
		(*it)->Release();
		delete (*it);
		_ListGameObjects.remove(*it);
	}
}