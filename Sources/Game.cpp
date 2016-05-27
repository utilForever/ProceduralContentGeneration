#include "PCH.h"
#include "Game.h"

// Default constructor.
Game::Game(sf::RenderWindow* window) :
m_window(*window),
m_gameState(GAME_STATE::PLAYING),
m_isRunning(true),
m_string(""),
m_screenSize({ 0, 0 }),
m_screenCenter({ 0, 0 }),
m_scoreTotal(0),
m_goldTotal(0),
m_projectileTextureID(0),
m_levelWasGenerated(false)
{
	// Enable VSync.
	m_window.setVerticalSyncEnabled(true);

	// Hide the mouse cursor.
	m_window.setMouseCursorVisible(false);

	// Calculate and store the center of the screen.
	m_screenCenter = { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f };

	// Create the level object.
	m_level = Level(*window);

	// Create the game font.
	m_font.loadFromFile("../../resources/fonts/ADDSBP__.TTF");
}

// Initializes the game.
void Game::Initialize()
{
	// Get the screen size.
	m_screenSize = m_window.getSize();

	// Load the correct projectile texture.
	m_projectileTextureID = TextureManager::AddTexture("../../resources/projectiles/spr_sword.png");

	// Initialize the UI.
	LoadUI();

	// Builds the light grid.
	ConstructLightGrid();

	// Define the game views.
	m_views[static_cast<int>(VIEW::MAIN)] = m_window.getDefaultView();
	m_views[static_cast<int>(VIEW::MAIN)].zoom(0.5f);
	m_views[static_cast<int>(VIEW::UI)] = m_window.getDefaultView();

	// Load the level.
	m_level.LoadLevelFromFile("../../resources/data/level_data.txt");

	// Set the position of the player.
	m_player.SetPosition(sf::Vector2f(m_screenCenter.x + 197.f, m_screenCenter.y + 410.f));

	// Populate level.
	PopulateLevel();
}

// Constructs the grid of sprites that are used to draw the game light system.
void Game::ConstructLightGrid()
{
	// Load the light tile texture and store a reference.
	int textureID = TextureManager::AddTexture("../../resources/spr_light_grid.png");
	sf::Texture& lightTexture = TextureManager::GetTexture(textureID);

	// Calculate the number of tiles in the grid. Each light tile is 25px square.
	sf::IntRect levelArea;

	// Define the bounds of the level.
	levelArea.left = static_cast<int>(m_level.GetPosition().x);
	levelArea.top = static_cast<int>(m_level.GetPosition().y);
	levelArea.width = m_level.GetSize().x * m_level.GetTileSize();
	levelArea.height = m_level.GetSize().y * m_level.GetTileSize();

	int width, height, lightTotal;

	width = levelArea.width / 25;
	height = levelArea.height / 25;

	lightTotal = width * height;

	// Create all tiles.
	for (int i = 0; i < lightTotal; i++)
	{
		// Create the tile.
		sf::Sprite lightSprite;

		// Set sprite texture.
		lightSprite.setTexture(lightTexture);

		// Set the position of the tile.
		int xPos = levelArea.left + ((i % width) * 25);
		int yPos = levelArea.top + ((i / width) * 25);

		lightSprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));

		// Add the sprite to our light vector.
		m_lightGrid.push_back(lightSprite);
	}
}

// Loads and prepares all UI assets.
void Game::LoadUI()
{
	// Initialize the player ui texture and sprite.
	m_playerUiSprite = std::make_shared<sf::Sprite>();
	m_playerUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_warrior_ui.png")));
	m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
	m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
	m_uiSprites.push_back(m_playerUiSprite);

	// Bar outlines.
	sf::Texture& barOutlineTexture = TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_bar_outline.png"));
	sf::Vector2f barOutlineTextureOrigin = { barOutlineTexture.getSize().x / 2.f, barOutlineTexture.getSize().y / 2.f };

	m_healthBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_healthBarOutlineSprite->setTexture(barOutlineTexture);
	m_healthBarOutlineSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_healthBarOutlineSprite);

	m_manaBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_manaBarOutlineSprite->setTexture(barOutlineTexture);
	m_manaBarOutlineSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_manaBarOutlineSprite);

	//Bars.
	sf::Texture& healthBarTexture = TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_health_bar.png"));
	sf::Vector2f barTextureOrigin = { healthBarTexture.getSize().x / 2.f, healthBarTexture.getSize().y / 2.f };

	m_healthBarSprite = std::make_shared<sf::Sprite>();
	m_healthBarSprite->setTexture(healthBarTexture);
	m_healthBarSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	m_manaBarSprite = std::make_shared<sf::Sprite>();
	m_manaBarSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_mana_bar.png")));
	m_manaBarSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	// Initialize the coin and gem ui sprites.
	m_gemUiSprite = std::make_shared<sf::Sprite>();
	m_gemUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_gem_ui.png")));
	m_gemUiSprite->setPosition(sf::Vector2f(m_screenCenter.x - 260.f, 50.f));
	m_gemUiSprite->setOrigin(sf::Vector2f(42.f, 36.f));
	m_uiSprites.push_back(m_gemUiSprite);

	m_coinUiSprite = std::make_shared<sf::Sprite>();
	m_coinUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_coin_ui.png")));
	m_coinUiSprite->setPosition(sf::Vector2f(m_screenCenter.x + 60.f, 50.f));
	m_coinUiSprite->setOrigin(sf::Vector2f(48.f, 24.f));
	m_uiSprites.push_back(m_coinUiSprite);

	// Key pickup sprite.
	m_keyUiSprite = std::make_shared<sf::Sprite>();
	m_keyUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../../resources/ui/spr_key_ui.png")));
	m_keyUiSprite->setPosition(sf::Vector2f(m_screenSize.x - 120.f, m_screenSize.y - 70.f));
	m_keyUiSprite->setOrigin(sf::Vector2f(90.f, 45.f));
	m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
	m_uiSprites.push_back(m_keyUiSprite);

	// Load stats.
	m_attackStatTextureIDs[0] = TextureManager::AddTexture("../../resources/ui/spr_attack_ui.png");
	m_attackStatTextureIDs[1] = TextureManager::AddTexture("../../resources/ui/spr_attack_ui_alt.png");

	m_attackStatSprite = std::make_shared<sf::Sprite>();
	m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[0]));
	m_attackStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_attackStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 270.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_attackStatSprite);

	m_defenseStatTextureIDs[0] = TextureManager::AddTexture("../../resources/ui/spr_defense_ui.png");
	m_defenseStatTextureIDs[1] = TextureManager::AddTexture("../../resources/ui/spr_defense_ui_alt.png");

	m_defenseStatSprite = std::make_shared<sf::Sprite>();
	m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[0]));
	m_defenseStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_defenseStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 150.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_defenseStatSprite);

	m_strengthStatTextureIDs[0] = TextureManager::AddTexture("../../resources/ui/spr_strength_ui.png");
	m_strengthStatTextureIDs[1] = TextureManager::AddTexture("../../resources/ui/spr_strength_ui_alt.png");

	m_strengthStatSprite = std::make_shared<sf::Sprite>();
	m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[0]));
	m_strengthStatSprite->setOrigin(sf::Vector2f(22.f, 12.f));
	m_strengthStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 30.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_strengthStatSprite);

	m_dexterityStatTextureIDs[0] = TextureManager::AddTexture("../../resources/ui/spr_dexterity_ui.png");
	m_dexterityStatTextureIDs[1] = TextureManager::AddTexture("../../resources/ui/spr_dexterity_ui_alt.png");

	m_dexterityStatSprite = std::make_shared<sf::Sprite>();
	m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[0]));
	m_dexterityStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_dexterityStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 90.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_dexterityStatSprite);

	m_staminaStatTextureIDs[0] = TextureManager::AddTexture("../../resources/ui/spr_stamina_ui.png");
	m_staminaStatTextureIDs[1] = TextureManager::AddTexture("../../resources/ui/spr_stamina_ui_alt.png");

	m_staminaStatSprite = std::make_shared<sf::Sprite>();
	m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[0]));
	m_staminaStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_staminaStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 210.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_staminaStatSprite);
}

// Populate the level with items.
void Game::PopulateLevel()
{

}

// Returns the running state of the game.
bool Game::IsRunning()
{
	return m_isRunning;
}

// Main game loop.
void Game::Run()
{
	float currentTime = m_timestepClock.restart().asSeconds();
	float timeDelta = 0.f;

	// Loop until there is a quite message from the window or the user pressed escape.
	while (m_isRunning)
	{
		// Check if the game was closed.
		sf::Event event;
		if (m_window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
			{
				m_window.close();
				return;
			}
		}

		float newTime = m_timestepClock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		// Update all items in the level.
		if (!m_levelWasGenerated)
		{
			Update(frameTime);

			// Draw all items in the level.
			Draw(frameTime);
		}
		else
		{
			m_levelWasGenerated = false;
		}
	}

	// Shut the game down.
	m_window.close();
}

// Updates the game.
void Game::Update(float timeDelta)
{
	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Main menu code ...
		break;

	case GAME_STATE::PLAYING:
	{
		// First check if the player is at the exit. If so there's no need to update anything.
		Tile& playerTile = *m_level.GetTile(m_player.GetPosition());

		if (playerTile.type == TILE::WALL_DOOR_UNLOCKED)
		{
			// ...
		}
		else
		{
			// Update the player.
			m_player.Update(timeDelta, m_level);

			// Store the player position as it's used many times.
			sf::Vector2f playerPosition = m_player.GetPosition();

			// If the player is attacking create a projectile.
			if (m_player.IsAttacking())
			{
				if (m_player.GetMana() >= 2)
				{
					sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
					std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::GetTexture(m_projectileTextureID), playerPosition, m_screenCenter, target);
					m_playerProjectiles.push_back(std::move(proj));

					// Reduce player mana.
					m_player.SetMana(m_player.GetMana() - 2);
				}
			}

			// Update all items.
			UpdateItems(playerPosition);

			// Update level light.
			UpdateLight(playerPosition);

			// Update all enemies.
			UpdateEnemies(playerPosition, timeDelta);

			// Update all projectiles.
			UpdateProjectiles(timeDelta);

			// Venter the view.
			m_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
		}
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Game over code
		break;
	}
}

// Updates the level light.
void Game::UpdateLight(sf::Vector2f playerPosition)
{
	for (sf::Sprite& sprite : m_lightGrid)
	{
		float tileAlpha = 255.f;			// Tile alpha.
		float distance = 0.f;				// The distance between player and tile.

		// Calculate distance between tile and player.
		distance = DistanceBetweenPoints(sprite.getPosition(), playerPosition);

		// Calculate tile transparency.
		if (distance < 200.f)
		{
			tileAlpha = 0.f;
		}
		else if (distance < 250.f)
		{
			tileAlpha = (51.f * (distance - 200.f)) / 10.f;
		}

		// Get all torches from the level.
		auto torches = m_level.GetTorches();

		// If there are torches.
		if (!torches->empty())
		{
			// Update the light surrounding each torch.
			for (std::shared_ptr<Torch> torch : *torches)
			{
				// If the light tile is within range of the torch.
				distance = DistanceBetweenPoints(sprite.getPosition(), torch->GetPosition());
				if (distance < 100.f)
				{
					// Edit its alpha.
					tileAlpha -= (tileAlpha - ((tileAlpha / 100.f) * distance)) * torch->GetBrightness();
				}
			}

			// Ensure alpha does not go negative.
			if (tileAlpha < 0)
			{
				tileAlpha = 0;
			}
		}

		// Set the sprite transparency.
		sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
	}
}

// Updates all items in the level.
void Game::UpdateItems(sf::Vector2f playerPosition)
{
	// Update all items.
	auto itemIterator = m_items.begin();
	while (itemIterator != m_items.end())
	{
		// Get the item from the iterator.
		Item& item = **itemIterator;

		// Check if the player is within pickup range of the item.
		if (DistanceBetweenPoints(item.GetPosition(), playerPosition) < 40.f)
		{
			// Check what type of object it was.
			switch (item.GetType())
			{
			case ITEM::GOLD:
			{
				// Get the amount of gold.
				int goldValue = dynamic_cast<Gold&>(item).GetGoldValue();

				// Add to the gold total.
				m_goldTotal += goldValue;
			}
			break;

			case ITEM::GEM:
			{
				// Get the score of the gem.
				int scoreValue = dynamic_cast<Gem&>(item).GetScoreValue();

				// Add to the score total
				m_scoreTotal += scoreValue;
			}
			break;

			case ITEM::KEY:
			{
				// Unlock the door.
				m_level.UnlockDoor();

				// Set the key as collected.
				m_keyUiSprite->setColor(sf::Color::White);
			}
			break;

			case ITEM::POTION:
			{
				// . . .
			}
			break;

			case ITEM::HEART:
				// Cast to heart and get health.
				Heart& heart = dynamic_cast<Heart&>(item);

				m_player.SetHealth(m_player.GetHealth() + heart.GetHealth());
			}

			// Finally, delete the object.
			itemIterator = m_items.erase(itemIterator);
		}
		else
		{
			// Increment iterator.
			++itemIterator;
		}
	}
}

// Updates all enemies in the level.
void Game::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta)
{
	// Store player tile.
	Tile* playerTile = m_level.GetTile(m_player.GetPosition());

	auto enemyIterator = m_enemies.begin();
	while (enemyIterator != m_enemies.end())
	{
		// Create a bool so we can check if an enemy was deleted.
		bool enemyWasDeleted = false;

		// Get the enemy object from the iterator.
		Enemy& enemy = **enemyIterator;

		// Get the tile that the enemy is on.
		Tile* enemyTile = m_level.GetTile(enemy.GetPosition());

		// Check for collisions with projectiles.
		auto projectilesIterator = m_playerProjectiles.begin();
		while (projectilesIterator != m_playerProjectiles.end())
		{
			// Get the projectile object from the iterator.
			Projectile& projectile = **projectilesIterator;

			// If the enemy and projectile occupy the same tile they have collided.
			if (enemyTile == m_level.GetTile(projectile.GetPosition()))
			{
				// Delete the projectile.
				projectilesIterator = m_playerProjectiles.erase(projectilesIterator);

				// Damage the enemy.
				enemy.Damage(25);

				// If the enemy is dead remove it.
				if (enemy.IsDead())
				{
					// Get the enemy position.
					sf::Vector2f position = enemy.GetPosition();

					// Spawn loot.
					for (int i = 0; i < 5; i++)
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
						std::unique_ptr<Item> item;

						switch (std::rand() % 2)
						{
						case 0: // Spawn gold.
							item = std::make_unique<Gold>();
							break;

						case 1: // Spawn gem.
							item = std::make_unique<Gem>();
							break;
						}

						item->SetPosition(position);
						m_items.push_back(std::move(item));
					}

					if ((std::rand() % 5) == 0)			// 1 in 5 change of spawning health.
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
						std::unique_ptr<Item> heart = std::make_unique<Heart>();
						heart->SetPosition(position);
						m_items.push_back(std::move(heart));
					}
					// 1 in 5 change of spawning potion.
					else if ((std::rand() % 5) == 1)
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
						std::unique_ptr<Item> potion = std::make_unique<Potion>();
						potion->SetPosition(position);
						m_items.push_back(std::move(potion));
					}

					// Delete enemy.
					enemyIterator = m_enemies.erase(enemyIterator);
					enemyWasDeleted = true;

					// Since the enemy is dead we no longer need to check projectiles.
					projectilesIterator = m_playerProjectiles.end();
				}
			}
			else
			{
				// Move to the next projectile.
				++projectilesIterator;
			}
		}

		// If the enemy was not deleted, update it and increment the iterator.
		if (!enemyWasDeleted)
		{
			enemy.Update(timeDelta);
			++enemyIterator;
		}

		// Check for collision with player.
		if (enemyTile == playerTile)
		{
			if (m_player.CanTakeDamage())
			{
				m_player.Damage(10);
			}
		}
	}
}

// Updates all projectiles in the level.
void Game::UpdateProjectiles(float timeDelta)
{
	auto projectileIterator = m_playerProjectiles.begin();
	while (projectileIterator != m_playerProjectiles.end())
	{
		// Get the projectile object from the iterator.
		Projectile& projectile = **projectileIterator;

		// Get the tile that the projectile is on.
		TILE projectileTileType = m_level.GetTile(projectile.GetPosition())->type;

		// If the tile the projectile is on is not floor, delete it.
		if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
		{
			projectileIterator = m_playerProjectiles.erase(projectileIterator);
		}
		else
		{
			// Update the projectile and move to the next one.
			projectile.Update(timeDelta);
			++projectileIterator;
		}
	}
}

// Calculates the distance between two given points.
float Game::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
	return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
}

// Draw the given string at the given position.
void Game::DrawString(std::string text, sf::Vector2f position, unsigned int size)
{
	// Clear the old data.
	m_stringStream.str(std::string());
	m_string.clear();

	m_stringStream << text;
	m_string = m_stringStream.str();

	m_text.setString(m_string);
	m_text.setFont(m_font);
	m_text.setCharacterSize(size);
	m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

	m_window.draw(m_text);
}

// Draw the current game scene.
void Game::Draw(float timeDelta)
{
	// Clear the screen.
	m_window.clear(sf::Color(3, 3, 3, 225));		// Gray

	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Draw main menu ...
		break;

	case GAME_STATE::PLAYING:
	{
		// Set the main game view.
		m_window.setView(m_views[static_cast<int>(VIEW::MAIN)]);

		// Draw the level.
		m_level.Draw(m_window, timeDelta);

		// Draw all objects.
		for (const auto& item : m_items)
		{
			item->Draw(m_window, timeDelta);
		}

		// Draw all enemies.
		for (const auto& enemy : m_enemies)
		{
			enemy->Draw(m_window, timeDelta);
		}

		// Draw all projectiles
		for (const auto& proj : m_playerProjectiles)
		{
			m_window.draw(proj->GetSprite());
		}

		// Draw the player.
		m_player.Draw(m_window, timeDelta);

		// Draw level light.
		for (const sf::Sprite& sprite : m_lightGrid)
		{
			m_window.draw(sprite);
		}

		// Switch to UI view.
		m_window.setView(m_views[static_cast<int>(VIEW::UI)]);

		// Draw player aim.
		m_window.draw(m_player.GetAimSprite());

		// Draw player stats.
		DrawString(std::to_string(m_player.GetAttack()), sf::Vector2f(m_screenCenter.x - 210.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetDefense()), sf::Vector2f(m_screenCenter.x - 90.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetStrength()), sf::Vector2f(m_screenCenter.x + 30.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetDexterity()), sf::Vector2f(m_screenCenter.x + 150.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetStamina()), sf::Vector2f(m_screenCenter.x + 270.f, m_screenSize.y - 30.f), 25);

		// Draw player score.
		std::string scoreString;

		if (m_scoreTotal > 99999)
		{
			scoreString = std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 9999)
		{
			scoreString = "0" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 999)
		{
			scoreString = "00" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 99)
		{
			scoreString = "000" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 9)
		{
			scoreString = "0000" + std::to_string(m_scoreTotal);
		}
		else
		{
			scoreString = "00000" + std::to_string(m_scoreTotal);
		}

		DrawString(scoreString, sf::Vector2f(m_screenCenter.x - 120.f, 40.f), 40);

		// Draw gold total.
		std::string goldString;

		if (m_goldTotal > 99999)
		{
			goldString = std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 9999)
		{
			goldString = "0" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 999)
		{
			goldString = "00" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 99)
		{
			goldString = "000" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 9)
		{
			goldString = "0000" + std::to_string(m_goldTotal);
		}
		else
		{
			goldString = "00000" + std::to_string(m_goldTotal);
		}

		DrawString(goldString, sf::Vector2f(m_screenCenter.x + 220.f, 40.f), 40);

		// Draw rest of the UI.
		for (const auto& sprite : m_uiSprites)
		{
			m_window.draw(*sprite);
		}

		// Draw the current room and floor.
		DrawString("Floor " + std::to_string(m_level.GetFloorNumber()), sf::Vector2f(70.f, m_screenSize.y - 65.f), 25);
		DrawString("Room " + std::to_string(m_level.GetRoomNumber()), sf::Vector2f(70.f, m_screenSize.y - 30.f), 25);

		// Draw health and mana bars.
		m_healthBarSprite->setTextureRect(sf::IntRect(0, 0, (213.f / m_player.GetMaxHealth()) * m_player.GetHealth(), 8));
		m_window.draw(*m_healthBarSprite);

		m_manaBarSprite->setTextureRect(sf::IntRect(0, 0, (213.f / m_player.GetMaxMana()) * m_player.GetMana(), 8));
		m_window.draw(*m_manaBarSprite);
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Draw game over screen ...
		break;
	}

	// Present the back-buffer to the screen.
	m_window.display();
}