#include "LevelEditorButton.h"

LevelEditorButton::LevelEditorButton(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	SetAlive(true);
}