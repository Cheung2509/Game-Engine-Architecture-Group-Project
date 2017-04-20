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
//class Collectables;
//class Platforms;
class Levels;
class Room;

class DebugCamera;
class CameraFollow2D;

class Game
{
public:

	Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance);
	virtual ~Game();

	bool Tick(); //tick the game state

	void Draw(ID3D11DeviceContext* _pd3dImmediateContext); //render the current game state

protected:
	DWORD m_playTime; //amount of time since the game started

	Camera* m_cam; //principle camera
	DebugCamera* m_debugCam2D;
	//CameraFollow2D* m_playerCam;
	Light* m_light; //base light

	TextGO2D* collects;
	TextGO2D* lives;
	TextGO2D* room;

	list<GameObject *> m_GameObjects; //data structure storing all GameObjects of this Game
	list<GameObject2D *> m_GameObject2Ds;//ditto 2D objects
	list<TextGO2D *> m_UserInterface;

	//required for the CMO model rendering system
	CommonStates* m_states;
	IEffectFactory* m_fxFactory;

	//direct input stuff
	bool ReadInput(); //Get current Mouse and Keyboard states
	IDirectInput8*			m_pDirectInput;
	IDirectInputDevice8*	m_pKeyboard;
	IDirectInputDevice8*	m_pMouse;
	unsigned char			m_keyboardState[256];
	unsigned char			m_prevKeyboardState[256];
	DIMOUSESTATE			m_mouseState;
	HWND m_hWnd;
	RECT window;

	GameData* m_GD;			//Data to be shared to all Game Objects as they are ticked
	DrawData* m_DD;			//Data to be shared to all Game Objects as they are drawn
	DrawData2D * m_DD2D;	//Data to be passed by game to all 2D Game Objects via Draw 

	Player2D* player;       // pointer to player class
	//Collectables* PickUp;   // pointer to pick up class
	//Collectables* Respawner;

	std::unique_ptr<Room>_Room = nullptr;

	//sound stuff
	std::unique_ptr<AudioEngine> m_audioEngine;

	//Tick functions for each state
	void PlayTick();
	void CollisionResolution(GameObject2D* object1, GameObject2D* object2);
	void CollisionManagement();
	//changes
	//list<GameObject2D*> m_collider;
};


#endif