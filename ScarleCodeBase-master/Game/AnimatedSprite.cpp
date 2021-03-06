#include "AnimatedSprite.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"


AnimatedSprite::AnimatedSprite(string _fileName, ID3D11Device* _GD, int frameCount): ImageGO2D(_fileName, _GD)
{
	m_frameCount = frameCount;
	m_totalElapsed = 0;
	m_frame = 0;
	m_timePerFrame = 0.33;
	
	ID3D11Resource* resource;
	m_pTextureRV->GetResource(&resource);

	D3D11_RESOURCE_DIMENSION dim;
	resource->GetType(&dim);

	D3D11_TEXTURE2D_DESC desc;
	((ID3D11Texture2D *)resource)->GetDesc(&desc);

	m_frameWidth = desc.Width;
	m_frameHeight = desc.Height;

	sourceRect = new RECT();
}

AnimatedSprite::~AnimatedSprite()
{
	if (sourceRect)
	{
		sourceRect = nullptr;
	}
}

void AnimatedSprite::Tick(GameData* _GD)
{
	ImageGO2D::Tick(_GD);
}

void AnimatedSprite::Draw(DrawData2D* _DD)
{
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, sourceRect, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
}