#include "PCH.h"
#include "Gold.h"

// Default constructor.
Gold::Gold()
{
	// Set gold value.
	this->goldValue = 15;

	// Set the sprite.
	int textureID;
	textureID = TextureManager::AddTexture("../../resources/loot/gold/spr_pickup_gold_medium.png");

	this->SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

	// Set the item type.
	m_type = ITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
	return this->goldValue;
}