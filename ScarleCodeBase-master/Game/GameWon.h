#pragma once
#include <windows.h>
#include <dinput.h>
//#include "Game.h"

class menu;
struct GameData;
class TextGO2D;
class GameWon
{
public:
	GameWon();
	~GameWon();
	void GameWonButtons(HWND& _hwnd, TextGO2D* GameRestart, TextGO2D* GameExit, GameData* m_GD);

private:
	TextGO2D* GameRestart;
	TextGO2D* GameExit;
	GameData* m_GD;
	RECT  virtualRectPlay;
	RECT virtualRectExit;
};

