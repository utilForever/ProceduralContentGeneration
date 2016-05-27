//-------------------------------------------------------------------------------------
// Object.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
	/**
	 * Default constructor.
	 */
	Object();

	/**
	 * Updates the game object. Called once per tick.
	 * This is a pure virtual function, and must be implemented by extending classes.
	 * @param timeDelta The time elapsed since the last tick in MS.
	 */
	virtual void Update(float timeDelta) {};

	/**
	 * Draws the object to the screen at its current position.
	 * @param window The render window to draw the object to.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void Draw(sf::RenderWindow &window, float timeDelta);

	/**
	 * Sets the position of the object on screen. This is relative to the top-left of the game window.
	 * @param position The new position of the player.
	 */
	void SetPosition(sf::Vector2f position);

	/** 
	 * Returns the position of the object. This is relative to the top-left of the game window.
	 * @return The position of the object
	 */
	sf::Vector2f GetPosition() const;

	/**
	 * Creates and sets the object sprite.
	 * This function takes the location to a resource, and from that create a texture and sprite.
	 * You can optionally specify animation properties. If set the frame dimensions will be calculated automatically.
	 * If left blank, the whole resource will be used.
	 * @param fileName The path to the resource that you wish to load, relative to the project.
	 * @param frames The number of frames in the sprite. Defaults to 1.
	 * @param frameSpeed The speed that the animation plays at. Defaults to 1.
	 * @return true if the operation succeeded.
	 */
	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);

	/**
	 * Returns a reference the object's sprite.
	 * @return A reference to the object's sprite.
	 */
	sf::Sprite& GetSprite();

	/**
	 * Get the number of frames the object has.
	 * @return The number of frames the object has.
	 */
	int GetFrameCount() const;

	/**
	 * Gets the current animation state of the object.
	 * @return The current animation state of the object.
	 */
	bool IsAnimated();

	/**
	* Sets the animation state of the object.
	* @param isAnimated The new animation state of the object.
	*/
	void SetAnimated(bool isAnimated);

protected:

	/**
	 * The object's sprite.
	 */
	sf::Sprite m_sprite;

	/**
	 * The position of the object in the game window.
	 */
	sf::Vector2f m_position;

private:

	/**
	 * Advances the sprite by a frame.
	 */
	void NextFrame();

private:
	/**
	 * The animation speed of the image if applicable.
	 * Value is frames per second.
	 */
	int m_animationSpeed;

	/**
	 * Used to determine if the given sprite is animated.
	 */
	bool m_isAnimated;

	/**
	 * The total number of frames the sprite has.
	 */
	int m_frameCount;

	/**
	 * The current frame of the sprite.
	 */
	int m_currentFrame;

	/**
	 * The width of each frame of the animated sprite if applicable.
	 */
	int m_frameWidth;

	/**
	 * The height of each frame of the animated sprite if applicable.
	 */
	int m_frameHeight;

	/**
	 * An aggregate of the time passed between draw calls.
	 */
	float m_timeDelta;
};
#endif