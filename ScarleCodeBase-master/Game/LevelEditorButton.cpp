#include "LevelEditorButton.h"

LevelEditorButton::LevelEditorButton(string _fileName, ID3D11Device* _GD) : Sprite(_fileName, _GD)
{
	SetAlive(true);
}