#include "CGame.h"

CGame::CGame() : 
	m_handleWindow(NULL), 
	m_lpDirect3D(NULL), 
	m_lpDirect3DDevice(NULL), 
	m_lpSpriteDirect3DHandle(NULL)
{
}

CGame::CGame(HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode)
{

}

CGame::~CGame()
{
	SAFE_RELEASE(m_lpDirect3D)
	SAFE_RELEASE(m_lpDirect3DDevice)
	SAFE_DELETE(m_handleWindow)
}

bool CGame::InitializeHandleWindow(HINSTANCE hInstance)
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbClsExtra		= 0;
	WndcEx.cbSize			= sizeof(WNDCLASSEX);
	WndcEx.cbWndExtra		= 0;
	WndcEx.hbrBackground	= (HBRUSH)COLOR_BACKGROUND;
	WndcEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	WndcEx.hIcon			= NULL;
	WndcEx.hIconSm			= NULL;
	WndcEx.hInstance		= hInstance;
	WndcEx.lpfnWndProc		= (WNDPROC)WndProceduce;
	WndcEx.lpszClassName	= "CGame";
	WndcEx.lpszMenuName		= NULL;
	WndcEx.style			= NULL;

	if(!RegisterClassEx(&WndcEx))
	{
		CGameLog::getInstance("CGame")->SaveError("Can't Regist the WndcEx!!!");
		return false;
	}


	m_handleWindow = CreateWindow(
		"CGame",
		GAMETITLE,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(!m_handleWindow)
	{
		CGameLog::getInstance("CGame")->SaveError("Can't Create Window!");
		return false;
	}

	ShowWindow(m_handleWindow, SW_SHOW);
	UpdateWindow(m_handleWindow);

	return true;
}

bool CGame::InitializeDirect3DEnvironment()
{
	this->m_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!this->m_lpDirect3D)
	{
		CGameLog::getInstance("CGame")->SaveError("Can't Create Direct3D Object!");
		return false;
	}

	return true;
}

bool CGame::InitializeDirect3DDevice(bool isWindowed)
{
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (isWindowed)
	{
		d3dpp.BackBufferCount	= 1;
		d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
		d3dpp.BackBufferHeight	= 600;
		d3dpp.BackBufferWidth	= 800;
		d3dpp.Windowed			= true;
		d3dpp.hDeviceWindow		= this->m_handleWindow;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD; 
	}
	else
	{
		D3DDISPLAYMODE DisPlayMode;
		ZeroMemory(&DisPlayMode, sizeof(DisPlayMode));

		m_lpDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisPlayMode);

		HRESULT handleResult;
		handleResult = m_lpDirect3D->CheckDeviceFormat(
			D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_HAL, 
			DisPlayMode.Format, 
			D3DUSAGE_RENDERTARGET, 
			D3DRTYPE_SURFACE, 
			D3DFMT_A8R8G8B8);

		if(FAILED(handleResult))
		{
			CGameLog::getInstance("CGame")->SaveError("Device format is unacceptable for full screen mode");
			return false;
		}

		d3dpp.BackBufferCount	= 1;
		d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
		d3dpp.Windowed			= false;
		d3dpp.BackBufferWidth	= DisPlayMode.Width;
		d3dpp.BackBufferHeight	= DisPlayMode.Height;
		d3dpp.hDeviceWindow		= this->m_handleWindow;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD; 
	}

	m_lpDirect3D->CreateDevice(
			  D3DADAPTER_DEFAULT,
			  D3DDEVTYPE_HAL,
			  m_handleWindow,
			  D3DCREATE_HARDWARE_VERTEXPROCESSING,
			  &d3dpp,
			  &m_lpDirect3DDevice);

	if(FAILED(m_lpDirect3DDevice))
	{
		CGameLog::getInstance("CGame")->SaveError("Can't create Direct3D Device");
		return false;
	}

	return true;
}

bool CGame::InitializeDirect3DSpriteHandle()
{
	D3DXCreateSprite(m_lpDirect3DDevice, &m_lpSpriteDirect3DHandle);
	HRESULT hr;
	hr = !FAILED(m_lpSpriteDirect3DHandle);

	if(!hr)
	{
		CGameLog::getInstance("CGame")->SaveError("Can't create Direct3D Sprite Handle");
		return false;
	}

	

	return true;
}

bool CGame::InitializeDirectSound()
{
	HRESULT hr;
	hr = DirectSoundCreate8(NULL, &m_lpDirectSound, NULL);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CGame")->SaveError("Can't Create Direct Sound!");
		return false;
	}
	hr = m_lpDirectSound->SetCooperativeLevel(this->m_handleWindow, DSSCL_PRIORITY);
	if(FAILED(hr))
	{
		CGameLog::getInstance("CGame")->SaveError("Can't Set Cooperative Level DSound!");
		return false;
	}
	return true;
}

bool CGame::Initialize(HINSTANCE hInstance, bool isWindowed)
{
	this->InitializeHandleWindow(hInstance);
	this->InitializeDirect3DEnvironment();
	this->InitializeDirect3DDevice(isWindowed);
	this->InitializeDirect3DSpriteHandle();
	this->InitializeDirectSound();
	
	CGameTimeDx9::getInstance()->InitGameTime();
	
	this->m_fps = 0;
	
	SoundManagerDx9::getInstance()->LoadAllSoundBuffer(m_lpDirectSound);
	
	CInputDx9::getInstance()->InitializeInput();
	CInputDx9::getInstance()->InitializeMouseDevice(m_handleWindow);
	CInputDx9::getInstance()->InitializeKeyBoardDevice(m_handleWindow);

	SpriteManager::getInstance()->InitializeListSprite(m_lpDirect3DDevice);

	StateManagerDx9::getInstance()->setDirectDevice(m_lpDirect3DDevice);
	StateManagerDx9::getInstance()->AddElement(new DemoState(eIDStateGame::INTRO));
	return true;
}

//int move_x_1 = 0;
//void XoayTron(int &x, int &y, float angle)
//{
//	//y = sin(x * 3.14 / 180.0) * 100 + 300;
//	//x += 1;
//	move_x_1 += 1;
//	x = (int)(move_x_1 + 40 * cos(angle));
//	//x = hoanh do tam xoay + ban kinh * cos(goc xoay)
//	y = (int)(300 + 40 * sin(angle));
//	//y = tung do tam xoay + ban kinh * sin(goc xoay)
//	
//}
//
//void HinhSin()
//{
//
//}
//
//int x_1 = 0;
//int y_1 = 300;
//float angle_1 = 0;

void CGame::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));


	while(!CGlobal::IsExit)
	{
		#pragma region Exit
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}  
		#pragma endregion

		else
		{
			CGameTimeDx9::getInstance()->UpdateGameTime();
			CInputDx9::getInstance()->UpdateKeyBoard();

			m_fps += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if( m_fps > 1000 / 60)
			{
				/*
				#pragma region Test input
				//texture->UpdateAnimation(m_GameTime, 50);
				#pragma endregion
				if (CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
				{
					m_UnitTest.x = --m_UnitTest.x;
					m_testSpriteEffect = eSpriteEffect::Horizontally;
				}
				if (CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
				{
					m_UnitTest.x = ++m_UnitTest.x;
					m_testSpriteEffect = eSpriteEffect::None;
				}
				if (CInputDx9::getInstance()->IsKeyDown(DIK_UP))
				{
					m_UnitTest.y = ++m_UnitTest.y;
					m_testSpriteEffect = eSpriteEffect::Vertically;
				}
				if (CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
				{
					m_UnitTest.y = --m_UnitTest.y;
					m_testSpriteEffect = eSpriteEffect::None;
				}
				Camera::getInstance()->UpdateCamera(&m_UnitTest);
				*/

				sprintf(fps, "milisecs per frame: %f \n", m_fps);

				OutputDebugString(fps);

				StateManagerDx9::getInstance()->Update();
				StateManagerDx9::getInstance()->HandleInput();

				m_lpDirect3DDevice->Clear(0 , 0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0); 
				D3DXMATRIX oldMatrix;
				m_lpSpriteDirect3DHandle->GetTransform(&oldMatrix);		
				m_lpSpriteDirect3DHandle->SetTransform(&Camera::getInstance()->GetMatrixTranslate());
				
				/*SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_1)->UpdateAnimation(m_GameTime, 50);
				*/

				if(m_lpDirect3DDevice->BeginScene())
				{
					m_lpSpriteDirect3DHandle->Begin(D3DXSPRITE_ALPHABLEND);

					/*
					//texture->Render(m_lpSpriteDirect3DHandle, &D3DXVECTOR3(0, 0, 0) , &D3DXVECTOR3(0, 0, 0), angle, eSpriteEffect::Horizontally, &D3DXVECTOR2(0, 0));
					//texture->Render(m_lpSpriteDirect3DHandle, D3DXVECTOR2(m_UnitTest.x, m_UnitTest.y), m_testSpriteEffect, 0.0f, 1.0f, 1.0f);
					//PhuongTrinhDuongThang(x_1, y_1);
					XoayTron(x_1, y_1, angle_1-=0.1f);
					//texture->Render(m_lpSpriteDirect3DHandle, D3DXVECTOR2(x_1, y_1), eSpriteEffect::None, 0.0f, 1.0f, 1.0f);
					SpriteManager::getInstance()->GetSprite(eSpriteID::BILL_MOVE_1)->Render(m_lpSpriteDirect3DHandle, D3DXVECTOR2(x_1, y_1), eSpriteEffect::None, 0.0f, 1.0f, 1.0f);
					*/

					StateManagerDx9::getInstance()->Render(m_lpSpriteDirect3DHandle);
					
					m_lpSpriteDirect3DHandle->End();
					m_lpDirect3DDevice->EndScene();
				}
				
				m_lpDirect3DDevice->Present(0, 0, 0, 0);
				m_fps = 0;
				m_lpSpriteDirect3DHandle->SetTransform(&oldMatrix);
			}
		}
	}
}

void CGame::Exit()
{
	SAFE_RELEASE(m_lpDirect3D)
	SAFE_RELEASE(m_lpDirect3DDevice)
	//SAFE_DELETE(m_GameTime);
	CInputDx9::getInstance()->Release();
	SoundManagerDx9::getInstance()->Release();
	SpriteManager::getInstance()->Release();
}

LRESULT CALLBACK CGame::WndProceduce(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message,wParam, lParam);
}