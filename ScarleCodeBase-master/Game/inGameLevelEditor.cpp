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
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(m_hWnd, &cursorPos);

	/*if ((cursorPos.x < (PlatformButton->GetPos().x + PlatformButton->getSpriteWidth())) &&
	(cursorPos.y < (PlatformButton->GetPos().x + PlatformButton->getSpriteWidth())))
	{*/
		if (_GD->m_mouseState->rgbButtons[0])
		{
			Vector2 camPos = Vector2(_DD->m_cam2D->GetPos());

			Vector2 camSize = Vector2(_DD->m_cam2D->getZoom(),_DD->m_cam2D->getZoom());

			Vector2 w_pos;
			cursorPos.x += camPos.x + (camSize.x);
			cursorPos.y += camPos.y + (camSize.y);

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

		