//-------------------------------------------------------------------------------------
// Gold.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef GOLD_H
#define GOLD_H

#include "Item.h"

class Gold : public Item
{
public:
	/**
	 * Default constructor.
	 */
	Gold();

	/**
	 * Gets the amount of gold this pickup has.
	 * @return The amount of gold the pickup has.
	 */
	int GetGoldValue() const;

private:
	/**
	 * The value of this gold pickup.
	 */
	int goldValue;
};
#endif