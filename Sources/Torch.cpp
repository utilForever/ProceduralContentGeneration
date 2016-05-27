#include "PCH.h"
#include "Torch.h"

// Default constructor.
Torch::Torch() :
m_brightness(1.f)
{
	// Set sprite.
	int textureID = TextureManager::AddTexture("../../resources/spr_torch.png");
	SetSprite(TextureManager::GetTexture(textureID), false, 5, 12);
}

// Update the brightness of the torch.
void Torch::Update(float timeDelta)
{
	// Generate a random number between 80 and 120, divide by 100 and store as float between .8 and 1.2.
	m_brightness = (std::rand() % 41 + 80) / 100.f;
}

// Returns the brightness of the torch.
float Torch::GetBrightness()
{
	return m_brightness;
}