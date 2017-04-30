#include "GameOver.h"
#include "GameState.h"
#include "GameObject2D.h"
#include "GameData.h"
#include "TextGO2D.h"

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

void GameOver::GameOverButtons()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(m_hWnd, &cursorPos);
	if ((cursorPos.x > virtualRectPlay.left && cursorPos.x < virtualRectPlay.right) &&
		(cursorPos.y > virtualRectPlay.top && cursorPos.y < virtualRectPlay.bottom))
	{
		/*GameExit->SetColour(Color((float*)&Colors::Yellow));*/
		if (m_GD->m_mouseState->rgbButtons[0])
		{
			m_GD->m_MS = MS_EXIT;
		}
	}
	else
	{
		/*GameExit->SetColour(Color((float*)&Colors::White));*/

	}
	if ((cursorPos.x > virtualRectExit.left && cursorPos.x < virtualRectExit.right) &&
		(cursorPos.y > virtualRectExit.top && cursorPos.y < virtualRectExit.bottom))
	{
		/*GameRestart->SetColour(Color((float*)&Colors::Yellow));*/
		if (m_GD->m_mouseState->rgbButtons[0])
		{
			m_GD->m_MS = MS_EXIT;
		}
	}
	else
	{
		/*GameRestart->SetColour(Color((float*)&Colors::White));*/
	}
}


