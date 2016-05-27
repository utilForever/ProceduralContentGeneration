//-------------------------------------------------------------------------------------
// Gem.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef GEM_H
#define GEM_H

#include "Item.h"

class Gem : public Item
{
public:
	/**
	 * Default constructor.
	 */
	Gem();

	/**
	 * Gets the amount of score this pickup gives.
	 * @return The amount of score the pickup gives.
	 */
	int GetScoreValue() const;

private:
	/**
	 * The value of this gem pickup.
	 */
	int m_scoreValue;
};
#endif