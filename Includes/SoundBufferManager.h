//-------------------------------------------------------------------------------------
// SoundBufferManager.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef SOUNDMANAGERBUFFER_H
#define SOUNDMANAGERBUFFER_H

class SoundBufferManager
{
public:
	/**
	 * Default constructor.
	 */
	SoundBufferManager();

	/**
	 * Adds a sound buffer to the manager, and returns its id in the map.
	 * @param filePath The path to the sound to load.
	 * @return The id to the sound buffer created, or the id in the map if it already exists.
	 */
	static int AddSoundBuffer(std::string filePath);

	/**
	 * Removes a sound buffer from the manager from a given id.
	 * @param soundBufferID The id of the sound buffer to be removed.
	 */
	static void RemoveSoundBuffer(int soundBufferID);

	/**
	 * Gets a sound buffer from its ID.
	 * @param soundBufferId The id of the sound buffer to return.
	 * @return A reference to the sound buffer.
	 */
	static sf::SoundBuffer& GetSoundBuffer(int soundBufferId);

private:
	/**
	 * A map of each sound name with its ID.
	 */
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> m_soundBuffers;

	/**
	 * The current key value.
	 */
	static int m_currentId;
};
#endif