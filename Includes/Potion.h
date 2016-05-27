//-------------------------------------------------------------------------------------
// Potion.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item
{
public:
	/**
	* Default constructor.
	*/
	Potion();

	/**
	 * Gets the attack value of the potion.
	 * @return The attack value the potion gives.
	 */
	int GetAttack() const;

	/**
	 * Gets the defense value of the potion.
	 * @return The defense value the potion gives.
	 */
	int GetDefense() const;

	/**
	 * Gets the strength value of the potion.
	 * @return The strength value the potion gives.
	 */
	int GetStrength() const;

	/**
	 * Gets the dexterity value of the potion.
	 * @return The dexterity value the potion gives.
	 */
	int GetDexterity() const;

	/**
	 * Gets the stamina value of the potion.
	 * @return The stamina value the potion gives.
	 */
	int GetStamina() const;

private:

	/**
	 * The attack value of the potion.
	 */
	int m_attack;

	/**
	 * The defense value of the potion.
	 */
	int m_defense;

	/**
	* The strength value of the potion.
	*/
	int m_strength;

	/**
	 * The dexterity value of the potion.
	 */
	int m_dexterity;

	/**
	 * The stamina value of the potion.
	 */
	int m_stamina;
};
#endif