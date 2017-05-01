#pragma once

#include <memory>
#include <vector>
#include <list>
#include <string>

#include"GameObject2D.h"
#include "Sprite.h"

class LevelEditorButton;
class Tile;
class Room;
class inGameLevelEditor
{
public:
	inGameLevelEditor(ID3D11Device* _pd3dDevice);
	~inGameLevelEditor()=default;
	void createButtons(ID3D11Device* _pd3dDevice);
	void createObject(GameData* _GD, Room* room, HWND m_hWnd);
	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);

private:
	LevelEditorButton* PlatformButton;
	Tile*  plat;

	Sprite* _platform;
	
	list<GameObject2D *> EditorObjects;//list to hold all objects created
	bool hasButtonBeenCreated;
};
