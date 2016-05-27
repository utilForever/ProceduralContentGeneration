//-------------------------------------------------------------------------------------
// Heart.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef HEART_H
#define HEART_H

#include "Item.h"

class Heart : public Item
{
public:

	/**
	 * Default constructor.
	 */
	Heart();

	/**
	 * Returns the amount of health that the heart gives.
	 * @return The amount of health the heart gives.
	 */
	int GetHealth() const;

private:

	/**
	 * The amount of health the heart gives.
	 */
	int m_health;
};
#endif