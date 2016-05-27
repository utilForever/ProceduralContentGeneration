//-------------------------------------------------------------------------------------
// Enemy.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"

class Entity : public Object
{
public:

	/**
	 * Default constructor.
	 */
	Entity();

	/**
	 * Override the default Object::Update function.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	virtual void Update(float timeDelta) override;

	/**
	 * Gets the entities health.
	 * @return The entities health.
	 */
	int GetHealth() const;

	/**
	 * Gets the entities max health.
	 * @return The entities max health.
	 */
	int GetMaxHealth() const;

	/**
	 * Gets the entities attack.
	 * @return The entities attack.
	 */
	int GetAttack() const;

	/**
	 * Gets the entities defense.
	 * @return The entities defense.
	 */
	int GetDefense() const;

	/**
	 * Gets the entities strength.
	 * @return The entities strength.
	 */
	int GetStrength() const;

	/**
	 * Gets the entities dexterity.
	 * @return The entities dexterity.
	 */
	int GetDexterity() const;

	/**
	 * Gets the entities stamina.
	 * @return The entities stamina.
	 */
	int GetStamina() const;

	/**
	 * Sets the entities attack stat.
	 * @param attackValue The player's new attack stat value.
	 */
	void SetAttack(int attackValue);

	/**
	 * Sets the entities defense stat.
	 * @param defenseValue The player's new defense stat value.
	*/
	 void SetDefense(int defenseValue);

	/**
	 * Sets the entities strength stat.
	 * @param strengthValue The player's new strength stat value.
	 */
	void SetStrength(int strengthValue);

	/**
	 * Sets the entities dexterity stat.
	 * @param dexterityValue The player's new dexterity stat value.
	 */
	void SetDexterity(int dexterityValue);

	/**
	 * Sets the entities stamina stat.
	 * @param staminaValue The player's new stamina stat value.
	 */
	void SetStamina(int staminaValue);

protected:
	/**
	 * A vector of all texture IDs.
	 */
	int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

	/**
	 * The index of the current texture.
	 */
	int m_currentTextureIndex;

	/**
	 * The entities current health.
	 */
	int m_health;

	/**
	 * The entities maximum health.
	 */
	int m_maxHealth;

	/**
	 * The entities current mana.
	 */
	int m_mana;

	/**
	 * The entities maximum mana.
	 */
	int m_maxMana;

	/**
	 * The entities attack stat. Effects damage dealt.
	 */
	int m_attack;

	/**
	 * The entities defense stat. Effects damage taken.
	 */
	int m_defense;

	/**
	 * The entities strength. Effects damage dealt.
	 */
	int m_strength;

	/**
	 * The entities dexterity. Effects movement speed.
	 */
	int m_dexterity;

	/**
	 * The entities stamina. Effects health.
	 */
	int m_stamina;

	/**
	 * The entities movement speed.
	 */
	int m_speed;

	/**
	 * The entities current velocity.
	 */
	sf::Vector2f m_velocity;
};
#endif