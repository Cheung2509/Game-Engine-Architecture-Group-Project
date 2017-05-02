#include "inGameLevelEditor.h"

#include "gamedata.h"
#include "DrawData2D.h"
#include "LevelEditorButton.h"
#include "Tile.h"
#include "Room.h"
#include "Camera2D.h"


inGameLevelEditor::inGameLevelEditor(ID3D11Device* _pd3dDevice)
{
	//PlatformButton = nullptr;
	hasButtonBeenCreated = false;

	_platform = new Sprite("Platform", _pd3dDevice);
	//plat = nullptr;
	createButtons(_pd3dDevice);
}

void inGameLevelEditor::Tick(GameData* _GD)
{
	/*for (auto& Object : EditorObjects)
	{
		Object->Tick(_GD);
	}*/
}

void inGameLevelEditor::createButtons(ID3D11Device* _pd3dDevice)
{
	if (!hasButtonBeenCreated)
	{
		PlatformButton = new LevelEditorButton("Platform", _pd3dDevice);
		PlatformButton->SetPos(Vector2(100, 100));
		PlatformButton->SetScale(1.0f);
		hasButtonBeenCreated = true;
	}
}

void inGameLevelEditor::createObject(GameData * _GD, Room* room, HWND m_hWnd, DrawData2D* _DD)
{
	/*if ((cursorPos.x < (PlatformButton->GetPos().x + PlatformButton->getSpriteWidth())) &&
	(cursorPos.y < (PlatformButton->GetPos().x + PlatformButton->getSpriteWidth())))
	{*/
		if (_GD->m_mouseState->rgbButtons[0])
		{
			//geting the cursor position relative to the screen
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			ScreenToClient(m_hWnd, &cursorPos);

			Vector2 camPos;
			camPos = _DD->m_cam2D->GetPos();

			Vector2 w_pos;

			w_pos.x = camPos.x + cursorPos.x - (_GD->viewportWidth / 2);
			w_pos.y = camPos.y + cursorPos.y - (_GD->viewportHeight / 2);

			plat = new Tile(_platform, w_pos);// 
			plat->setType(PLATFORM);
			room->addToLists(plat);
		}
	//}
}

void inGameLevelEditor::Draw(DrawData2D* _DD)
{
	/*for (auto& Object : EditorObjects)
	{
		if (Object->isAlive())
		{
			Object->Draw(_DD);
		}
	}*/
	PlatformButton->Draw(_DD);
}

		