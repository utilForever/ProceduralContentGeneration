#include "PCH.h"
#include "Heart.h"

// Default constructor.
Heart::Heart()
{
	// Set item sprite.
	SetSprite(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/loot/heart/spr_pickup_heart.png")), false, 8, 12);

	// Set health value.
	m_health = 15;

	// Set item type.
	m_type = ITEM::HEART;
}

// Returns the amount of health that the heart gives.
int Heart::GetHealth() const
{
	return m_health;
}