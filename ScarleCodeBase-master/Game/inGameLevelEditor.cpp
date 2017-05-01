#include "inGameLevelEditor.h"

#include "gamedata.h"

#include "LevelEditorButton.h"
#include "Tile.h"
#include "Room.h"


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

void inGameLevelEditor::createObject(GameData * _GD, Room* room, HWND m_hWnd)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(m_hWnd, &cursorPos);

	/*if ((cursorPos.x > PlatformButton->get && cursorPos.x < PlatformButton->GetPos().x) &&
		(cursorPos.y > PlatformButton->GetPos().y && cursorPos.y < PlatformButton->GetPos().y))
	{*/
		if (_GD->m_mouseState->rgbButtons[0])
		{
			plat = new Tile(_platform, Vector2(cursorPos.x, cursorPos.y));// 
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

		