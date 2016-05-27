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
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Level.h"

class Enemy : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Enemy();

	/**
	 * Applies the given amount of damage to the enemy.
	 * @param damage The amount of damage to deal to the enemy.
	 */
	void Damage(int damage);

	/**
	 * Checks if the enemy has taken enough damage that they are now dead.
	 * @return True if the enemy is dead.
	 */
	bool IsDead();
};
#endif