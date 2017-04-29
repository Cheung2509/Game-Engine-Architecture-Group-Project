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


#include "DebugCamera.h"
#include "CameraFollow2D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance)
{
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

	//create a background
	BackG = new Background("background", _pd3dDevice);

	//create first level
	Levels::load();
	m_Room.reset(Levels::LoadedLevels[0].createRoom());
	m_Room->CreateRoom(m_GD, _pd3dDevice);
	player = m_Room->getPlayer(); //set games copy of player 


	//create DrawData struct and populate its pointers
	m_DD = new DrawData;
	m_DD->m_pd3dImmediateContext = nullptr;
	m_DD->m_states = m_states;
	m_DD->m_cam = m_cam;
	m_DD->m_light = m_light;


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
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
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
	case GS_PAUSE:
		break;
	case GS_GAME_OVER:
		break;
	case GS_PLAY_MAIN_CAM:
		PlayTick();
		break;
	case GS_PLAY_DEBUG_CAM:
		PlayTick();
		break;
	}
	return true;
};

void Game::PlayTick()
{
	if ((m_keyboardState[DIK_SPACE] & 0x80) && !(m_prevKeyboardState[DIK_SPACE] & 0x80))
	{
		if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
		{
			std::cout << "State Changed";
			m_GD->m_GS = GS_PLAY_DEBUG_CAM;
		}
		else
		{
			std::cout << "State Changed";
			m_GD->m_GS = GS_PLAY_MAIN_CAM;
		}
	}

	CollisionManagement();

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

void Game::CollisionResolution(GameObject2D * object1, GameObject2D * object2)
{
	if (object1->GetType() != ObjectType::LADDER)
	{
		switch (object1->GetType())
		{
		case ObjectType::ENEMY:
			if (object1->GetType() == ObjectType::ENEMY)
			{
				if (player->getLives() != 0)
				{
					std::cout << "Enemy hit \n";
					player->SetAlive(false);
					player->TakeLives();
					if (m_Room->getRespawner()->GetRespawnUp())
					{
						player->SetAlive(true);
						player->SetPos(m_Room->getRespawner()->GetPos());
						player->SetPlayerState(PlayerState::PlayerState_IDLE);
					}
					else
					{
						player->SetAlive(true);
						player->SetPos(Vector2(200, 450));
					}
					player->SetZeroVel(0);

				}
				else
				{
					player->SetAlive(false);
				}

			}
			break;
		case ObjectType::COLLECTIBLE:
			if (m_Room->getCollectable()->GetPickedUp() == false)// could change this 
			{
				std::cout << "Collected \n";
				player->addCollectable();
				object1->SetAlive(false);
				m_Room->getCollectable()->SetPickeduP();
			}
			break;

		case ObjectType::PLATFORM:
			/*if (player->GetPlayerState() != PlayerState::PlayerState_JUMP)
			{
			player->SetIsGrounded(true);
			player->SetSpeedY(0.0f);
			}*/
			if (player->GetPosY() < object1->GetPosY())
			{
				//top collision
				player->SetIsGrounded(true);
				player->SetSpeedY(0.0f);
			}
			/*else if (player->GetPosY() > object1->GetPosY())
			{
				//bottom collision
				player->SetSpeedY(20.0f);
			}*/

			break;

		case::ObjectType::RESPAWN:
			m_Room->getRespawner()->SetRespawnUp(true);
			break;
		case ObjectType::MOTHER:
			//stop player from moving through // this dosnt work might give it to tim to look at 
			if (player->getSpeed() > 0)
			{
				player->SetSpeed(player->getSpeed() + - 20.0f);
			}
			else if (player->getSpeed() < 0)
			{
				player->SetSpeed(player->getSpeed()+20.0f);
			}
			if (player->getSpeedY() > 0)
			{
				player->SetSpeedY(player->getSpeedY() + -20.0f);
			}
			else if (player->getSpeedY() < 0)
			{
				player->SetSpeedY(player->getSpeedY() + 20.0f);
			}
			break;

		}
	}
	else
	{
		object2->SetIsGrounded(true);
		object2->setHasJumped(false);
		object2->SetSpeedY(0.0f);
		//object2->setSpeed(0.0f);
		object2->setOnLadder(true);
	}

}

void Game::CollisionManagement()
{
	for each(GameObject2D* object1 in m_Room->getColldingObjects())
	{
		if (object1->GetType() != ObjectType::PLAYER)
		{
			for each(GameObject2D* object2 in m_Room->getColldingObjects())
			{
				if (object2->GetType() == ObjectType::PLAYER && object2->isAlive())
				{
					if (object1->checkCollisions(object2))
					{
						CollisionResolution(object1, object2);
						return;
					}
					else
					{

						//player->SetPlayerState(PlayerState::PlayerState_IDLE);
						player->SetIsGrounded(false);
						player->setOnLadder(false);

					}
				}
				
			}
		}
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
		cout << "DebugCam \n";
		m_DD2D->m_cam2D = m_debugCam2D;
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
	m_DD2D->m_Sprites->Begin( SpriteSortMode::SpriteSortMode_BackToFront,
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
	m_Room->Draw(m_DD2D);
	m_DD2D->m_Sprites->End();

	m_DD2D->m_Sprites->Begin();

	for (list<TextGO2D*>::iterator it = m_UserInterface.begin(); it != m_UserInterface.end(); it++)
	{
		(*it)->Draw(m_DD2D);
	}
	m_DD2D->m_Sprites->End();

	//drawing text screws up the Depth Stencil State, this puts it back again!
	_pd3dImmediateContext->OMSetDepthStencilState(m_states->DepthDefault(), 0);
};



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