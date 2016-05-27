#include "PCH.h"
#include "Player.h"

// Constructor.
Player::Player() :
m_attackDelta(0.f),
m_damageDelta(0.f),
m_manaDelta(0.f),
m_isAttacking(false),
m_canTakeDamage(true)
{
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../../resources/players/warrior/spr_warrior_idle_left.png");

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
	m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));

	// Create the player's aim sprite.
	int textureID = TextureManager::AddTexture("../../resources/ui/spr_aim.png");
	m_aimSprite.setTexture(TextureManager::GetTexture(textureID));
	m_aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
	m_aimSprite.setScale(2.f, 2.f);

	// Set stats.
	m_health = m_maxHealth = 100;
	m_mana = m_maxMana = 50;
	m_speed = 200;

	m_attack = 10;
	m_defense = 10;
	m_strength = 10;
	m_dexterity = 10;
	m_stamina = 10;

}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	// Calculate movement speed based on the timeDelta since the last update.
	sf::Vector2f movementSpeed(0.f, 0.f);
	sf::Vector2f previousPosition = m_position;

	// Calculate where the current movement will put us.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);

	if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
	{
		// Set movement speed.
		movementSpeed.x = -m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_LEFT;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
	{
		// Set movement speed.
		movementSpeed.x = m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_RIGHT;
	}

	if (Input::IsKeyPressed(Input::KEY::KEY_UP))
	{
		// Set movement speed.
		movementSpeed.y = -m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_UP;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
	{
		// Set movement speed.
		movementSpeed.y = m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_DOWN;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
	{
		m_position.x = previousPosition.x;
	}
	else
	{
		m_position.x += movementSpeed.x;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
	{
		m_position.y = previousPosition.y;
	}
	else
	{
		m_position.y += movementSpeed.y;
	}

	// update the sprite position
	m_sprite.setPosition(m_position);

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}

	// set animation speed
	if ((movementSpeed.x == 0) && (movementSpeed.y == 0))
	{
		// the character is still
		if (IsAnimated())
		{
			// Update sprite to idle version.
			// In our enum we have 4 walking sprites followed by 4 idle sprites.
			// Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
			m_currentTextureIndex += 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Stop movement animations.
			SetAnimated(false);
		}
	}
	else
	{
		// the character is moving
		if (!IsAnimated())
		{
			// Update sprite to walking version.
			m_currentTextureIndex -= 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Calculate aim based on mouse.
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	m_aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

	// Check if shooting.
	if ((m_attackDelta += timeDelta) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
		{
			// Mark player as attacking.
			m_isAttacking = true;
		}
	}

	// Determine if the player can take damage.
	if (!m_canTakeDamage)
	{
		if ((m_damageDelta += timeDelta) > 1.f)
		{
			m_canTakeDamage = true;
			m_damageDelta = 0.f;
		}
	}

	// Increase player mana.
	if ((m_manaDelta += timeDelta) > 0.20)
	{
		if (m_mana < m_maxMana)
		{
			m_mana += 1;
		}

		m_manaDelta = 0.f;
	}
}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
	return m_aimSprite;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
	if (m_isAttacking)
	{
		m_isAttacking = false;
		m_attackDelta = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Checks if the player can take damage.
bool Player::CanTakeDamage()
{
	return m_canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
	m_health -= damage;

	if (m_health < 0)
	{
		m_health = 0;
	}

	m_canTakeDamage = false;
}

// Checks is the given movement will result in a collision.
bool Player::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
	Tile* overlappingTiles[4];
	sf::Vector2f newPosition = m_position + movement;

	// Top left.
	overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

	// Top right.
	overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

	// Bottom left.
	overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

	// Bottom right.
	overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

	// If any of the overlapping tiles are solid there was a collision.
	for (int i = 0; i < 4; i++)
	{
		if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
			return true;
	}

	// If we've not returned yet no collisions were found.
	return false;
}

// Gets the player's mana.
int Player::GetMana() const
{
	return m_mana;
}

// Gets the player's max mana.
int Player::GetMaxMana() const
{
	return m_maxMana;
}

// Set the player's mana level.
void Player::SetMana(int manaValue)
{
	if (manaValue >= 0)
	{
		m_mana = manaValue;
	}
}

// Set the player's health.
void Player::SetHealth(int healthValue)
{
	m_health = healthValue;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}