#include "Sprite.h"
#include <memory>
Sprite::Sprite(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	ID3D11Resource* resource;
	m_pTextureRV->GetResource(&resource);

	D3D11_RESOURCE_DIMENSION dim;
	resource->GetType(&dim);

	D3D11_TEXTURE2D_DESC desc;
	((ID3D11Texture2D *)resource)->GetDesc(&desc);

	m_spriteHeight = desc.Height;
	m_spriteWidth = desc.Width;
}

Sprite::~Sprite()
{
}
