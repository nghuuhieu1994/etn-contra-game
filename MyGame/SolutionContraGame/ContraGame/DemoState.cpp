#include "DemoState.h"

void DemoState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
		//texture->LoadContent(m_lpDirect3DDevice, "resources\\Character\\Bill\\bullet.png", 1, 1, 1, 0xffff00ff);
	texture = SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_JUMP);
	billmove1 = SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_1);
	billmove2 =	SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_2);
	billmove3 =	SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_3);
	billmove4 =	SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_4);

	for(int i = 0; i < 3; i++)
	{
		billmove5[i] =	SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_5);
	}
	backGround = SpriteManager::getInstance()->GetSprite(eSpriteID::BACKGROUND);
	billjump  =	SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_JUMP);	
	fBullet  =	SpriteManager::getInstance()->GetSprite(eSpriteID::F_BULLET);	
	m_UnitTest.x = 400;
	m_UnitTest.y = 300;
	m_UnitTest.z = 0;
	m_testSpriteEffect = eSpriteEffect::None;
}

int move_x_1 = 0;
int speedX= 1;
int speedY = 1;
float angle_1 = 0;
float scale = 0.1f;
int flag = 1;
float _x_1 = 100;
float _y_1 = 300;
float _x2 = 200;
float _y2 = 300;
float _x3 = 0;
float _y3 = 100;
float _x_j = 400;
float _y_j = 0;
void Rotate(float &x, float &y, float angle)
{
	if(move_x_1 >= 750 || move_x_1 < 0 )
		speedX *= -1;
	move_x_1 += 3*speedX;
	x = move_x_1 + 40 * cos(angle);
	//x = hoanh do tam xoay + ban kinh * cos(goc xoay)
	y = 300 + 40 * sin(angle);
	//y = tung do tam xoay + ban kinh * sin(goc xoay)
	
}

void Diagonal(float &x, float &y)
{
	y = x + 5;
	x += 2*speedX;
}

void Sin(float &x, float &y)
{
	y = sin(x * 3.14 / 180.0) * 50 + 200;
	if(x >= 800)
		speedX *= -1;
	x += 2*speedX;
}

void Scale(float &s)
{
	if(s == 1.0f || s == 2.0f)
		flag *= -1;
	s = s + (flag * 0.01f);
}

void Jump(float &x, float &y)
{
	x = 100;
	if(y > 600 || y < 0)
		speedY *= -1;
	y += 2*speedY;
	
}
	

void DemoState::HandleInput()
{
}
void DemoState::Update()
{
	texture->UpdateAnimation(100);
	billmove1->UpdateAnimation(200);
	billmove2->UpdateAnimation(200);
	billmove3->UpdateAnimation(200);
	for(int i = 0; i < 3; i++)
	{
		billmove5[i]->UpdateAnimation(200);
	}
	billjump->UpdateAnimation(200);
	fBullet->UpdateAnimation(200);
	
}
void DemoState::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
		Rotate(_x_1, _y_1, angle_1-=0.1f);
		Diagonal(_x2, _y2);
		Scale(scale);
		Jump(_x_j, _y_j);
		Sin(_x3, _y3);
		backGround->Render(_lpDSpriteHandle, D3DXVECTOR2(400 + sin(angle_1), 300 + cos(angle_1)), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
		texture->Render(_lpDSpriteHandle, D3DXVECTOR2(m_UnitTest.x, m_UnitTest.y), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
		billmove1->Render(_lpDSpriteHandle, D3DXVECTOR2(_x_1, _y_1), m_testSpriteEffect, 0.0f, 2.0f, 1.0f);
		fBullet->Render(_lpDSpriteHandle, D3DXVECTOR2(_x_1 + 100, _y_1 + 100), m_testSpriteEffect, 0.0f, 2.0f, 1.0f);
		billmove5[0]->Render(_lpDSpriteHandle, D3DXVECTOR2(_x_1 + 30, _y_1 + 50), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
		billmove5[1]->Render(_lpDSpriteHandle, D3DXVECTOR2(_x_1 - 50, _y_1 + 70), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
		billmove5[2]->Render(_lpDSpriteHandle, D3DXVECTOR2(_x_1 + 70, _y_1 + 100), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
		billmove2->Render(_lpDSpriteHandle, D3DXVECTOR2(_x2, _y2), m_testSpriteEffect, 0.0f, scale, 1.0f);
		billmove3->Render(_lpDSpriteHandle, D3DXVECTOR2(_x3, _y3), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
		billjump->Render(_lpDSpriteHandle, D3DXVECTOR2(_x_j, _y_j), m_testSpriteEffect, 0.0f, 2.0f, 1.0f);

}
void DemoState::Pause()
{}
void DemoState::Resume()
{}
void DemoState::Release()
{
	texture = NULL;
	billmove1 = NULL;
	billmove2 = NULL;
	billmove3 = NULL;
	billmove5[0] = NULL;
	billmove5[1] = NULL;
	billmove5[2] = NULL;
	billjump = NULL;
	fBullet = NULL;
}