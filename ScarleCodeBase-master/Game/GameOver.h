#pragma once
#include <windows.h>
#include <dinput.h>
#include "Game.h"

class menu;
struct GameData;
class TextGO2D;


class GameOver
{
public:
	GameOver();
	~GameOver();

	void GameOverButtons();
private:

	HWND m_hWnd;
	TextGO2D* GameRestart;
	TextGO2D* GameExit;
	GameData* m_GD;
	RECT  virtualRectPlay;
	RECT virtualRectExit;
};

