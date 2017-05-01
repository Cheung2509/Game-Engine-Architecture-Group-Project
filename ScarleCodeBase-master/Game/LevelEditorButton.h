#pragma once
#include "ImageGO2D.h"
#include "Sprite.h"
class LevelEditorButton : public Sprite
{
public:
	LevelEditorButton(string _fileName, ID3D11Device* _GD);
	~LevelEditorButton()=default;

private:

};