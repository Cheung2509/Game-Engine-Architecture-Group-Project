#ifndef _GAME_H_
#define _GAME_H_

//=================================================================
//Basic Game Manager Class
//=================================================================

#include <windows.h>
#include <list>
#include <dinput.h>
#include "Effects.h"
#include "CommonStates.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "Audio.h"

using std::list;
using std::unique_ptr;
using namespace DirectX;

// Forward declarations
class GameObject;
class GameObject2D;
class Camera;
class TPSCamera;
struct GameData;
struct DrawData;
struct DrawData2D;
class Light;
class TextGO2D;

class Player2D;
class MotherObstacle;
class Background;
class Levels;
class Room;
class inGameLevelEditor;


class Menu;
class GameOver;
class GameWon;



class DebugCamera;
class CameraFollow2D;
class CollisionManager;

class Game
{
public:

	Game(ID3D11Device* _pd, HWND _hWnd, HINSTANCE _hInstance);
	virtual ~Game();

	bool Tick(); //tick the game state

	void Draw(ID3D11DeviceContext* _pd3dImmediateContext); //render the current game state

protected:
	DWORD m_playTime; //amount of time since the game started

	Camera* m_cam; //principle camera
	DebugCamera* m_debugCam2D;
	//CameraFollow2D* m_playerCam;
	Light* m_light; //base light
	inGameLevelEditor* inGameEditor;

	TextGO2D* collects;
	TextGO2D* lives;
	TextGO2D* room;

	TextGO2D* MenuTitle;
	TextGO2D* MenuStart;
	TextGO2D* MenuExit;
	TextGO2D* GameRestart;
	TextGO2D* GameExit;
	TextGO2D* GameWonTxt;
	
	
	list<GameObject *> m_GameObjects; //data structure storing all GameObjects of this Game
	list<GameObject2D *> m_GameObject2Ds;//ditto 2D objects
	list<TextGO2D *> m_UserInterface;
	list<TextGO2D*> m_MainMenuText;
	list<TextGO2D*> m_GameOverText;
	//required for the CMO model rendering system
	CommonStates* m_states;
	IEffectFactory* m_fxFactory;
	ID3D11Device* _pd3dDevice;

	//direct input stuff
	bool ReadInput(); //Get current Mouse and Keyboard states
	IDirectInput8*			m_pDirectInput;
	IDirectInputDevice8*	m_pKeyboard;
	IDirectInputDevice8*	m_pMouse;
	unsigned char			m_keyboardState[256];
	unsigned char			m_prevKeyboardState[256];
	DIMOUSESTATE			m_mouseState;
	DIMOUSESTATE			m_prevMouseState;
	HWND m_hWnd;
	RECT window;

	GameData* m_GD;			//Data to be shared to all Game Objects as they are ticked
	DrawData* m_DD;			//Data to be shared to all Game Objects as they are drawn
	DrawData2D * m_DD2D;	//Data to be passed by game to all 2D Game Objects via Draw 
	CollisionManager* collisionManager;
	//Room* room_ptr;
	GameOver* gameOver;
	/*Collectables*collectable;*/

	Player2D* player;       // pointer to player class
	Background* BackG;
	Menu* mainMenu;
	Menu* GameOverMenu;
	Menu* GameWonMenu;
	GameWon* gamewon;
	std::unique_ptr<Room> m_Room = nullptr;

	//sound stuff
	std::unique_ptr<AudioEngine> m_audioEngine;
	std::unique_ptr<SoundEffect> m_ambient;
	std::unique_ptr<DirectX::SoundEffectInstance> m_Loop;

	//Tick functions for each state
	void PlayTick();

	//changes
	//list<GameObject2D*> m_collider;

	


};


#endif