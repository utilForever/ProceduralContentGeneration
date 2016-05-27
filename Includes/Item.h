//-------------------------------------------------------------------------------------
// Item.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ITEM_H
#define ITEM_H

#include <sstream>
#include <fstream>
#include "Object.h"

class Item : public Object
{
public:
	/**
	 * Default constructor.
	 */
	Item();

	/**
	 * Draws the item name to screen if it has one. The drawing of the object is done in the parent function which is called.
	 * @param window The render window to draw to.
	 * @param font The font to use when drawing the item name.
	 */
	void Draw(sf::RenderWindow& window, float timeDelta);

	/**
	 * Gets the name of the item.
	 * @return The name of the item.
	 */
	std::string GetItemName() const;

	/**
	 * Gets the item type.
	 * @return The item type.
	 */
	ITEM GetType() const;

protected:
	/**
	 * Sets the item name.
	 * @param name The new item name.
	 */
	void SetItemName(std::string name);

public:
	/**
	 * The name of the item.
	 */
	std::string m_name;

	/**
	 * The type of item.
	 */
	ITEM m_type;

	/**
	 * A text object storing the name of the item.
	 */
	sf::Text m_text;

	/**
	 * A font object storing the name of the item.
	 */
	sf::Font m_font;

	/*
	 * The dimensions of the items name in text.
	 */
	sf::Vector2f m_textOffset;
};
#endif