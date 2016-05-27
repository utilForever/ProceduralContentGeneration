#include "PCH.h"
#include "Potion.h"

// Default constructor.
Potion::Potion() :
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0)
{
	// Load and set sprite.
	SetSprite(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/loot/potions/spr_potion_stamina.png")), false, 8, 12);

	// Set the item type.
	m_type = ITEM::POTION;
}

// Gets the attack value of the potion.
int Potion::GetAttack() const
{
	return m_attack;
}

// Gets the defense value of the potion.
int Potion::GetDefense() const
{
	return m_defense;
}

// Gets the strength value of the potion.
int Potion::GetStrength() const
{
	return m_strength;
}

// Gets the dexterity value of the potion.
int Potion::GetDexterity() const
{
	return m_dexterity;
}

// Gets the stamina value of the potion.
int Potion::GetStamina() const
{
	return m_stamina;
}