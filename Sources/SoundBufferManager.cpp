#include "PCH.h"

std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> SoundBufferManager::m_soundBuffers;
int SoundBufferManager::m_currentId = 0;

// Default Constructor.
SoundBufferManager::SoundBufferManager()
{
}

// Adds a sound to the manager, and returns its id in the map.
int SoundBufferManager::AddSoundBuffer(std::string filePath)
{
	// First check if the sound has already been created. If so, simply return that one.
	auto it = m_soundBuffers.find(filePath);

	if (it != m_soundBuffers.end())
	{
		return it->second.first;
	}

	// At this point the texture doesn't exists, so we'll create and add it.
	m_currentId++;

	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
	if (!buffer->loadFromFile(filePath))
	{
		return -1;
	}

	m_soundBuffers.insert(std::make_pair(filePath, std::make_pair(m_currentId, std::move(buffer))));

	// Return the texture.
	return m_currentId;
}

// Gets a texture from the texture manager from an ID.
sf::SoundBuffer& SoundBufferManager::GetSoundBuffer(int textureId)
{
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
	{
		if (it->second.first == textureId)
		{
			return *it->second.second;
		}
	}
}