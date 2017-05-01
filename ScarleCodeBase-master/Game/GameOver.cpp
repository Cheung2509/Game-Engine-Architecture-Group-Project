#include "GameOver.h"
#include "GameState.h"
#include "GameObject2D.h"
#include "GameData.h"
#include "TextGO2D.h"
#include <DirectXColors.h>

GameOver::GameOver()
{
	virtualRectPlay.left = 580;
	virtualRectPlay.right = 680; //virtual rectangle around button may give colour
	virtualRectPlay.bottom = 229;
	virtualRectPlay.top = 180;
	virtualRectExit.left = 580;
	virtualRectExit.right = 680;
	virtualRectExit.bottom = 290;
	virtualRectExit.top = 230;
}

GameOver::~GameOver()
{
}

void GameOver::GameOverButtons(HWND& _hwnd, TextGO2D* GameRestart, TextGO2D* GameExit, GameData* m_GD)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(_hwnd, &cursorPos);
	if ((cursorPos.x > virtualRectPlay.left && cursorPos.x < virtualRectPlay.right) &&
		(cursorPos.y > virtualRectPlay.top && cursorPos.y < virtualRectPlay.bottom))
	{
		GameRestart->SetColour(Color((float*)&Colors::Yellow));
		if (m_GD->m_mouseState->rgbButtons[0])
		{
			m_GD->m_MS = MS_PLAY;
		}
	}
	else
	{
		GameRestart->SetColour(Color((float*)&Colors::White));

	}
	if ((cursorPos.x > virtualRectExit.left && cursorPos.x < virtualRectExit.right) &&
		(cursorPos.y > virtualRectExit.top && cursorPos.y < virtualRectExit.bottom))
	{
		GameExit->SetColour(Color((float*)&Colors::Yellow));
		if (m_GD->m_mouseState->rgbButtons[0])
		{
			m_GD->m_MS = MS_EXIT;
		}
	}
	else
	{
		GameExit->SetColour(Color((float*)&Colors::White));
	}
}


