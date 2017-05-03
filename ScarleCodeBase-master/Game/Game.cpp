#include "Game.h"
//DXTK headers
#include "SimpleMath.h"

//system headers
#include <windows.h>
#include <time.h>
#include <iostream>
#include <fstream>


//our headers
#include "ObjectList.h"
#include "GameData.h"
#include "drawdata.h"
#include "DrawData2D.h"
#include "Background.h"

#include "Menu.h"
#include "inGameLevelEditor.h"
#include "MotherObstecle.h"

#include "CollisionManager.h"
#include "GameOver.h"
#include "GameWon.h"
#include "DebugCamera.h"
#include "CameraFollow2D.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;


Game::Game(ID3D11Device* _pd, HWND _hWnd, HINSTANCE _hInstance)
{
	_pd3dDevice = _pd;
	//set up audio
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audioEngine.reset(new AudioEngine(eflags));

	//Create DirectXTK spritebatch stuff
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	m_DD2D = new DrawData2D();
	m_DD2D->m_Sprites.reset(new SpriteBatch(pd3dImmediateContext));
	m_DD2D->m_Font.reset(new SpriteFont(_pd3dDevice, L"..\\Assets\\italic.spritefont"));

	//seed the random number generator
	srand((UINT)time(NULL));

	//Direct Input Stuff
	m_hWnd = _hWnd;
	m_pKeyboard = nullptr;
	m_pDirectInput = nullptr;

	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = m_pKeyboard->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	hr = m_pMouse->SetDataFormat(&c_dfDIMouse);
	hr = m_pMouse->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//create GameData struct and populate its pointers
	m_GD = new GameData;
	m_GD->m_keyboardState = m_keyboardState;
	m_GD->m_prevKeyboardState = m_prevKeyboardState;
	m_GD->m_GS = GS_PLAY_MAIN_CAM;
	m_GD->m_mouseState = &m_mouseState;
	m_GD->m_prevMouseState = &m_prevMouseState;
	m_GD->m_MS = MS_MAIN;

	//set up DirectXTK Effects system
	m_fxFactory = new EffectFactory(_pd3dDevice);

	//Tell the fxFactory to look to the correct build directory to pull stuff in from
#ifdef DEBUG
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Debug");
#else
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Release");
#endif

	// Create other render resources here
	m_states = new CommonStates(_pd3dDevice);

	//find how big my window is to correctly calculate my aspect ratio
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	float AR = (float)width / (float)height;

	m_debugCam2D = new DebugCamera();
	m_debugCam2D->SetPos(Vector2(0, 0));
	m_debugCam2D->SetRot(0.0f);
	m_GameObject2Ds.push_back(m_debugCam2D);

	//create a base light
	m_light = new Light(Vector3(0.0f, 100.0f, 160.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(0.4f, 0.1f, 0.1f, 1.0f));
	m_GameObjects.push_back(m_light);

	GetWindowRect(m_hWnd, &window);
	m_GD->viewportHeight = window.bottom;
	m_GD->viewportWidth = window.left;

	//create menu sprite
	mainMenu = new Menu("BackgroundOther", _pd3dDevice);
	mainMenu->SetScale(0.6f);
	mainMenu->SetPos(Vector2(570, 300));

	GameOverMenu = new Menu("tried", _pd3dDevice);
	GameOverMenu->SetScale(0.6f);
	GameOverMenu->SetPos(Vector2(300, 300));

	GameWonMenu = new Menu("moon", _pd3dDevice);
	GameWonMenu->SetScale(0.6f);
	GameWonMenu->SetPos(Vector2(570, 300));

	//create a background
	BackG = new Background("BackGroundCity", _pd3dDevice);

	//create first level
	Levels::load();
	m_Room.reset(Levels::LoadedLevels[0].createRoom());
	m_Room->CreateRoom(m_GD, _pd3dDevice);
	player = m_Room->getPlayer(); //set games copy of player 

	//Audio
	m_ambient= std::make_unique<SoundEffect>(m_audioEngine.get(), L"..\\Assets\\GameMusic.wav");
	m_Loop = m_ambient->CreateInstance();
	//create DrawData struct and populate its pointers
	m_DD = new DrawData;
	m_DD->m_pd3dImmediateContext = nullptr;
	m_DD->m_states = m_states;
	m_DD->m_cam = m_cam;
	m_DD->m_light = m_light;

	MenuStart = new TextGO2D("PLAY");
	MenuStart->SetPos(Vector2(600, 200));
	MenuStart->SetScale(0.7);
	MenuStart->SetColour(Color((float*)&Colors::White));
	m_MainMenuText.push_back(MenuStart);

	MenuExit = new TextGO2D("EXIT");
	MenuExit->SetPos(Vector2(600, 250));
	MenuExit->SetScale(0.7);
	MenuExit->SetColour(Color((float*)&Colors::White));
	m_MainMenuText.push_back(MenuExit);

	GameWonTxt = new TextGO2D("CONGRATULATIONS YOU ARE A WINNER");
	GameWonTxt->SetPos(Vector2(100, 100));
	GameWonTxt->SetScale(0.7);
	GameWonTxt->SetColour(Color((float*)&Colors::White));
	

	GameExit = new TextGO2D("EXIT");
	GameExit->SetPos(Vector2(600, 250));
	GameExit->SetScale(0.7);
	GameExit->SetColour(Color((float*)&Colors::White));
	m_GameOverText.push_back(GameExit);

	GameRestart = new TextGO2D("RESTART");
	GameRestart->SetPos(Vector2(600, 200));
	GameRestart->SetScale(0.7);
	GameRestart->SetColour(Color((float*)&Colors::White));
	m_GameOverText.push_back(GameRestart);

	collects = new TextGO2D("Collectables: ");
	collects->SetPos(Vector2(10, 525));
	collects->SetScale(0.7);
	collects->SetColour(Color((float*)&Colors::Yellow));
	m_UserInterface.push_back(collects);

	lives = new TextGO2D("Lives: ");
	lives->SetPos(Vector2(10, 560));
	lives->SetScale(0.7);
	lives->SetColour(Color((float*)&Colors::Yellow));
	m_UserInterface.push_back(lives);

	room = new TextGO2D("roomname");
	room->SetPos(Vector2(300, 500));
	room->SetScale(0.7);
	room->SetColour(Color((float*)&Colors::Yellow));
	m_UserInterface.push_back(room);

	collisionManager = new CollisionManager();
};


Game::~Game()
{
	//delete Game Data & Draw Data
	delete m_GD;
	delete m_DD;

	//tidy away Direct Input Stuff
	if (m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
	}
	if (m_pMouse)
	{
		m_pMouse->Unacquire();
		m_pMouse->Release();
	}
	if (m_pDirectInput)
	{
		m_pDirectInput->Release();
	}

	//get rid of the game objects here
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		delete (*it);
	}
	m_GameObjects.clear();


	//and the 2D ones
	for (list<GameObject2D *>::iterator it = m_GameObject2Ds.begin(); it != m_GameObject2Ds.end(); it++)
	{
		delete (*it);
	}
	m_GameObject2Ds.clear();

	//clear away CMO render system
	delete m_states;
	delete m_fxFactory;

	delete m_DD2D;

};

bool Game::Tick()
{
	
	//tick audio engine
	if (!m_audioEngine->Update())
	{
		// No audio device is active
		if (m_audioEngine->IsCriticalError())
		{
			//something has gone wrong with audio so QUIT!
			return false;
		}
	}

	//Poll Keyboard & Mouse
	ReadInput();

	//Upon pressing escape QUIT
	if ((m_keyboardState[DIK_ESCAPE] & 0x80) || (m_GD->m_MS == MS_EXIT))
	{
		return false;
	}
	

	//m_GD->viewportHeight = window.bottom;
	//m_GD->viewportWidth = window.left;

	//calculate frame time-step dt for passing down to game objects
	DWORD currentTime = GetTickCount();
	m_GD->m_dt = min((float)(currentTime - m_playTime) / 1000.0f, 0.1f);
	m_playTime = currentTime;

	//start to a VERY simple FSM
	switch (m_GD->m_GS)
	{
	case GS_ATTRACT:
		break;
	case GS_GAME_OVER:
		break;
	case GS_PLAY_MAIN_CAM:
		PlayTick();
		break;
	case GS_PLAY_DEBUG_CAM:
		PlayTick();
		inGameEditor->createObject(m_GD, m_Room.get(), m_hWnd, m_DD2D);
		inGameEditor->Tick(m_GD);
		break;
	}
	return true;
};

void Game::PlayTick()
{
	if (m_Room->getMother() != NULL)
	{
		if (m_Room->getMother()->getBlocking() == false)
		{

			m_GD->m_MS = MS_GAMEWON;
		}
	}
	if (m_GD->m_MS == MS_GAMEWON)
	{
		gamewon = new GameWon();
		gamewon->GameWonButtons(m_hWnd, GameRestart, GameExit, m_GD);
		player->setLives(3);
		player->setCollectables(0);
		player->SetPos(m_Room->getPlayerSpawn());
		m_Room->getRespawner()->SetRespawnUp(false);
		m_Room->setCollectableAlive();
		m_Room->getMother()->setBlocking(true);
	}
	if (m_GD->m_MS == MS_PLAY)
	{
		if (m_Loop)
		{
			m_Loop->Play(true);
		}
			
	}
	if (m_Room->getMother()!=nullptr)//getMother()->getBlocking())
	{
	/*	if (!m_Room->getMother()->getBlocking())
		{
			m_GD->m_MS = MS_GAMEOVER;
		}*/
	}
	if (player->getLives() <= 0)
	{
		m_GD->m_MS = MS_GAMEOVER;
	}
	if ((m_keyboardState[DIK_M] & 0x80) && !(m_prevKeyboardState[DIK_M] & 0x80))//NEVER PRESS M!!!
	{
		m_DD2D->m_cam2D->SetRot(180.0f);
	}
	if (m_GD->m_MS == MS_GAMEOVER)
	{
		
		gameOver = new GameOver();
		gameOver->GameOverButtons(m_hWnd, GameRestart, GameExit, m_GD);
		player->setLives(3);
		player->setCollectables(0);
		player->SetPos(m_Room->getPlayerSpawn());
		if (m_Room->getRespawner() != nullptr)
		{
			m_Room->getRespawner()->SetRespawnUp(false);
		}
		m_Room->setCollectableAlive();
		if (m_Room->getMother() != nullptr)
		{
			m_Room->getMother()->setBlocking(true);
		}
		m_Room->restPrevRoom();
	}
	if (m_GD->m_MS == MS_MAIN)
	{
		RECT  virtualRectPlay;
		RECT virtualRectExit;
		virtualRectPlay.left = 580;
		virtualRectPlay.right = 680; //virtual rectangle around button may give colour
		virtualRectPlay.bottom = 229;
		virtualRectPlay.top = 180;
		virtualRectExit.left = 580;
		virtualRectExit.right = 680;
		virtualRectExit.bottom = 290;
		virtualRectExit.top = 230;
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(m_hWnd, &cursorPos);
		if ((cursorPos.x > virtualRectPlay.left && cursorPos.x < virtualRectPlay.right) &&
			(cursorPos.y > virtualRectPlay.top && cursorPos.y < virtualRectPlay.bottom))
		{
			MenuStart->SetColour(Color((float*)&Colors::Yellow));
			if (m_GD->m_mouseState->rgbButtons[0])
			{
				m_GD->m_MS = MS_PLAY;
			}
		}
		else
		{
			MenuStart->SetColour(Color((float*)&Colors::White));

		}
		if ((cursorPos.x > virtualRectExit.left && cursorPos.x < virtualRectExit.right) &&
			(cursorPos.y > virtualRectExit.top && cursorPos.y < virtualRectExit.bottom))
		{
			MenuExit->SetColour(Color((float*)&Colors::Yellow));
			if (m_GD->m_mouseState->rgbButtons[0])
			{
				m_GD->m_MS = MS_EXIT;
			}
		}
		else
		{
			MenuExit->SetColour(Color((float*)&Colors::White));
		}
	}
	else
	{

		if ((m_GD->m_MS == MS_PAUSE) && (m_keyboardState[DIK_P] & 0x80) && !(m_prevKeyboardState[DIK_P] & 0x80))
		{
			m_GD->m_MS = MS_PLAY;
		}
		else if ((m_keyboardState[DIK_P] & 0x80) && !(m_prevKeyboardState[DIK_P] & 0x80))
		{
			m_GD->m_MS = MS_PAUSE;
			Sleep(100);
		}

		collisionManager->checkCollision(m_Room.get());

		if ((m_keyboardState[DIK_SPACE] & 0x80) && !(m_prevKeyboardState[DIK_SPACE] & 0x80))
		{
			if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
			{
				m_GD->m_GS = GS_PLAY_DEBUG_CAM;
				inGameEditor = new inGameLevelEditor(_pd3dDevice);
				//inGameEditor->createButtons(_pd3dDevice);
			}
			else
			{
				m_GD->m_GS = GS_PLAY_MAIN_CAM;
			}
		}
		if (m_GD->m_MS == MS_PAUSE)
		{
		}
		else
		{

			if (m_Room->getLevelIncrease())
			{
				
				m_Room->setCurrentLevel(m_Room->getCurrentLevel() + 1);
				m_Room->ChangeLevel(m_GD, _pd3dDevice);
				m_Room->setLevelIncrease(false);
			}
			if (m_Room->getLevelDecrease())
			{
				
				m_Room->setCurrentLevel(m_Room->getCurrentLevel() - 1);
				m_Room->ChangeLevel(m_GD, _pd3dDevice);
				m_Room->setLevelDecrease(false);
			}


			//update all objects
			for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Tick(m_GD);
			}
			m_Room->Tick(m_GD);
			for (list<GameObject2D *>::iterator it = m_GameObject2Ds.begin(); it != m_GameObject2Ds.end(); it++)
			{
				(*it)->Tick(m_GD);
			}
		}

		collisionManager->checkCollision(m_Room.get());
	}
}

void Game::Draw(ID3D11DeviceContext* _pd3dImmediateContext)
{
	room->SetText(m_Room->getRoomName());
	collects->SetText("My Collectables: " + to_string(player->getCollectables()));//changed 
	lives->SetText("My lives: " + to_string(player->getLives())); //THIS SETS UPS LIVES  line above shows how to write to it  //changed 

																  //set immediate context of the graphics device
	m_DD->m_pd3dImmediateContext = _pd3dImmediateContext;

	//set which camera to be used
	m_DD->m_cam = m_cam;

	switch (m_GD->m_GS)
	{
	case GS_PLAY_DEBUG_CAM:
		m_DD2D->m_cam2D = m_debugCam2D;
		std::cout << "X: " << m_DD2D->m_cam2D->GetPos().x << 
			"  Y: " << m_DD2D->m_cam2D->GetPos().y << std::endl;
		break;
	case GS_PLAY_MAIN_CAM:
		//	cout << "PlayerCam \n";
		m_DD2D->m_cam2D = m_Room->getPlayerCamera();//cahnged this line 
		break;
	}

	//draw all objects
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Draw(m_DD);
	}

	// Draw sprite batch stuff 
	m_DD2D->m_Sprites->Begin(SpriteSortMode::SpriteSortMode_BackToFront,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_DD2D->m_cam2D->getTransform());

	for (list<GameObject2D *>::iterator it = m_GameObject2Ds.begin(); it != m_GameObject2Ds.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->Draw(m_DD2D);
		}
	}

	if (m_Room->getPlayer()->isAlive())
	{
		BackG->Draw(m_DD2D);
	}

	if (m_GD->m_GS == GameState::GS_PLAY_DEBUG_CAM)
	{
		inGameEditor->Draw(m_DD2D);
	}

	m_Room->Draw(m_DD2D);
	m_DD2D->m_Sprites->End();

	m_DD2D->m_Sprites->Begin();

	for (list<TextGO2D*>::iterator it = m_UserInterface.begin(); it != m_UserInterface.end(); it++)
	{
		(*it)->Draw(m_DD2D);
	}
	if (m_GD->m_MS == MS_GAMEOVER)//Draw Game Over menu
	{
		GameOverMenu->Draw(m_DD2D);
		for (list<TextGO2D*>::iterator it = m_GameOverText.begin(); it != m_GameOverText.end(); it++)
		{
			(*it)->Draw(m_DD2D);
		}
	}
	if (m_GD->m_MS == MS_GAMEWON)//Draw Game Over menu
	{
		GameWonMenu->Draw(m_DD2D);
		for (list<TextGO2D*>::iterator it = m_GameOverText.begin(); it != m_GameOverText.end(); it++)
		{
			(*it)->Draw(m_DD2D);
		}
		GameWonTxt->Draw(m_DD2D);
	}
	if (m_GD->m_MS == MS_MAIN) //Draw Main Menu
	{
		mainMenu->Draw(m_DD2D);
		for (list<TextGO2D*>::iterator it = m_MainMenuText.begin(); it != m_MainMenuText.end(); it++)
		{
			(*it)->Draw(m_DD2D);
		}
	}
	else
	{
	}

	m_DD2D->m_Sprites->End();

	//drawing text screws up the Depth Stencil State, this puts it back again!
	_pd3dImmediateContext->OMSetDepthStencilState(m_states->DepthDefault(), 0);
}



bool Game::ReadInput()
{
	//copy over old keyboard state
	memcpy(m_prevKeyboardState, m_keyboardState, sizeof(unsigned char) * 256);

	//clear out previous state
	ZeroMemory(&m_keyboardState, sizeof(unsigned char) * 256);
	ZeroMemory(&m_mouseState, sizeof(DIMOUSESTATE));

	// Read the keyboard device.
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	// Read the Mouse device.
	hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(hr))
	{
		// If the Mouse lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pMouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}