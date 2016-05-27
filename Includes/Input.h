//-------------------------------------------------------------------------------------
// Input.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef INPUT_H
#define INPUT_H

class Input
{
public:

	/**
	 * An enum denoting all possible input keys.
	 */
	enum class KEY
	{
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_ATTACK,
		KEY_ESC
	};

	/**
	 * Checks if a given key is currently pressed.
	 * @param keycode The key to check.
	 * @return True if the given key is currently pressed.
	 */
	static bool IsKeyPressed(KEY keycode);
};
#endif