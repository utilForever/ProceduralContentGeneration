#include "PCH.h"
#include "Level.h"

// Default constructor.
Level::Level()
{
}

// Constructor.
Level::Level(sf::RenderWindow& window) : 
m_origin({ 0, 0 }),
m_floorNumber(1),
m_roomNumber(0),
m_doorTileIndices({ 0, 0 })
{
	// Load all tiles.
	AddTile("../../resources/tiles/spr_tile_floor.png", TILE::FLOOR);

	AddTile("../../resources/tiles/spr_tile_wall_top.png", TILE::WALL_TOP);
	AddTile("../../resources/tiles/spr_tile_wall_top_left.png", TILE::WALL_TOP_LEFT);
	AddTile("../../resources/tiles/spr_tile_wall_top_right.png", TILE::WALL_TOP_RIGHT);
	AddTile("../../resources/tiles/spr_tile_wall_top_t.png", TILE::WALL_TOP_T);
	AddTile("../../resources/tiles/spr_tile_wall_top_end.png", TILE::WALL_TOP_END);

	AddTile("../../resources/tiles/spr_tile_wall_bottom_left.png", TILE::WALL_BOTTOM_LEFT);
	AddTile("../../resources/tiles/spr_tile_wall_bottom_right.png", TILE::WALL_BOTTOM_RIGHT);
	AddTile("../../resources/tiles/spr_tile_wall_bottom_t.png", TILE::WALL_BOTTOM_T);
	AddTile("../../resources/tiles/spr_tile_wall_bottom_end.png", TILE::WALL_BOTTOM_END);

	AddTile("../../resources/tiles/spr_tile_wall_side.png", TILE::WALL_SIDE);
	AddTile("../../resources/tiles/spr_tile_wall_side_left_t.png", TILE::WALL_SIDE_LEFT_T);
	AddTile("../../resources/tiles/spr_tile_wall_side_left_end.png", TILE::WALL_SIDE_LEFT_END);
	AddTile("../../resources/tiles/spr_tile_wall_side_right_t.png", TILE::WALL_SIDE_RIGHT_T);
	AddTile("../../resources/tiles/spr_tile_wall_side_right_end.png", TILE::WALL_SIDE_RIGHT_END);

	AddTile("../../resources/tiles/spr_tile_wall_intersection.png", TILE::WALL_INTERSECTION);
	AddTile("../../resources/tiles/spr_tile_wall_single.png", TILE::WALL_SINGLE);

	AddTile("../../resources/tiles/spr_tile_wall_entrance.png", TILE::WALL_ENTRANCE);
	AddTile("../../resources/tiles/spr_tile_door_locked.png", TILE::WALL_DOOR_LOCKED);
	AddTile("../../resources/tiles/spr_tile_door_unlocked.png", TILE::WALL_DOOR_UNLOCKED);

	// Calculate the top left of the grid.
	m_origin.x = (window.getSize().x - (GRID_WIDTH * TILE_SIZE));
	m_origin.x /= 2;

	m_origin.y = (window.getSize().y - (GRID_HEIGHT * TILE_SIZE));
	m_origin.y /= 2;

	// Store the column and row information for each node.
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			auto cell = &m_grid[i][j];
			cell->columnIndex = i;
			cell->rowIndex = j;
		}
	}
}

// Create and adds a tile sprite to the list of those available.
int Level::AddTile(std::string fileName, TILE tileType)
{
	// Add the texture to the texture manager.
	int textureID = TextureManager::AddTexture(fileName);

	if (textureID < 0)
	{
		return -1; // Failed
	}
	else
	{
		m_textureIDs[static_cast<int>(tileType)] = textureID;
	}

	// Return the ID of the tile.
	return textureID;
}

// Checks if a given tile is passable
bool Level::IsSolid(int i, int j)
{
	// Check that the tile is valid
	if (TileIsValid(i, j))
	{
		int tileIndex = static_cast<int>(m_grid[i][j].type);
		return (((tileIndex != static_cast<int>(TILE::FLOOR)) && (tileIndex != static_cast<int>(TILE::FLOOR_ALT))) && (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED)));
	}
	else
		return false;
}

// Returns the position of the level relative to the application window.
sf::Vector2f Level::GetPosition() const
{
	return sf::Vector2f(static_cast<float>(m_origin.x), static_cast<float>(m_origin.y));
}

// Returns the id of the given tile in the 2D level array.
TILE Level::GetTileType(int columnIndex, int rowIndex) const
{
	// Check that the parameters are valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT))
	{
		return TILE::EMPTY; // failed
	}

	// Fetch the id.
	return m_grid[columnIndex][rowIndex].type;
}

// Sets the id of the given tile in the grid.
void Level::SetTile(int columnIndex, int rowIndex, TILE tileType)
{
	// Check that the provided tile index is valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT))
	{
		return;
	}

	// check that the sprite index is valid
	if (tileType >= TILE::COUNT)
	{
		return;
	}

	// change that tiles sprite to the new index
	m_grid[columnIndex][rowIndex].type = tileType;
	m_grid[columnIndex][rowIndex].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(tileType)]));
}

// Gets the current floor number.
int Level::GetFloorNumber() const
{
	return m_floorNumber;
}

// Gets the current room number.
int Level::GetRoomNumber() const
{
	return m_roomNumber;
}

// Checks if a given tile is valid.
bool Level::TileIsValid(int column, int row)
{
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}

// Gets the size of the level in terms of tiles.
sf::Vector2i Level::GetSize() const
{
	return sf::Vector2i(GRID_WIDTH, GRID_HEIGHT);
}

// Gets the tile that the position lies on.
Tile* Level::GetTile(sf::Vector2f position)
{
	// Convert the position to relative to the level grid.
	position.x -= m_origin.x;
	position.y -= m_origin.y;

	// Convert to a tile position.
	int tileColumn, tileRow;

	tileColumn = static_cast<int>(position.x) / TILE_SIZE;
	tileRow = static_cast<int>(position.y) / TILE_SIZE;

	return &m_grid[tileColumn][tileRow];
}

// Returns a pointer to the tile at the given index.
Tile* Level::GetTile(int columnIndex, int rowIndex)
{
	if (TileIsValid(columnIndex, rowIndex))
	{
		return &m_grid[columnIndex][rowIndex];
	}
	else
	{
		return nullptr;
	}
}

// Loads a level from a .txt file.
bool Level::LoadLevelFromFile(std::string fileName)
{
	// Create all the fields we need.
	std::ifstream file(fileName);

	// Read level data into 2D int array that describes the level.
	if (file.is_open())
	{
		for (int j = 0; j < GRID_HEIGHT; ++j)
		{
			for (int i = 0; i < GRID_WIDTH; ++i)
			{
				// Get the cell that we're working on.
				auto& cell = m_grid[i][j];

				// Read the character. Out of 4 characters we only want 2nd and 3rd.
				std::string input;

				file.get();
				input += file.get();
				input += file.get();
				file.get();

				// Convert string to int.
				std::stringstream convert(input);
				int tileID;
				convert >> tileID;

				// Set type, sprite and position.
				cell.type = static_cast<TILE>(tileID);
				cell.sprite.setTexture(TextureManager::GetTexture(m_textureIDs[tileID]));
				cell.sprite.setPosition(m_origin.x + (TILE_SIZE * i), m_origin.y + (TILE_SIZE * j));

				// Check for entry/exit nodes.
				if (cell.type == TILE::WALL_DOOR_LOCKED)
				{
					// Save the location of the exit door.
					m_doorTileIndices = sf::Vector2i(i, 0);
				}
			}

			// Read end line char.
			file.get();
		}

		file.close(); //closing the file

		// Create torches at specific locations.
		sf::Vector2i locations[5];

		locations[0] = { m_origin.x + (3 * TILE_SIZE) + (TILE_SIZE / 2), m_origin.y + (9 * TILE_SIZE) + (TILE_SIZE / 2) };
		locations[1] = { m_origin.x + (7 * TILE_SIZE) + (TILE_SIZE / 2), m_origin.y + (7 * TILE_SIZE) + (TILE_SIZE / 2) };
		locations[2] = { m_origin.x + (11 * TILE_SIZE) + (TILE_SIZE / 2), m_origin.y + (11 * TILE_SIZE) + (TILE_SIZE / 2) };
		locations[3] = { m_origin.x + (13 * TILE_SIZE) + (TILE_SIZE / 2), m_origin.y + (15 * TILE_SIZE) + (TILE_SIZE / 2) };
		locations[4] = { m_origin.x + (15 * TILE_SIZE) + (TILE_SIZE / 2), m_origin.y + (3 * TILE_SIZE) + (TILE_SIZE / 2) };

		// Spawn torches.
		for (int i = 0; i < 5; ++i)
		{
			std::shared_ptr<Torch> torch = std::make_shared<Torch>();
			torch->SetPosition(sf::Vector2f(static_cast<float>(locations[i].x), static_cast<float>(locations[i].y)));
			m_torches.push_back(torch);
		}
	}
	else
	{
		return false;
	}

	return true;
}

// Checks if a given tile is a wall block.
bool Level::IsWall(int i, int j)
{
	if (TileIsValid(i, j))
		return m_grid[i][j].type <= TILE::WALL_INTERSECTION;
	else
		return false;
}

// Unlocks the door in the level.
void Level::UnlockDoor()
{
	SetTile(m_doorTileIndices.x, m_doorTileIndices.y, TILE::WALL_DOOR_UNLOCKED);
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(int columnIndex, int rowIndex)
{
	Tile* tile = &m_grid[columnIndex][rowIndex];

	return ((tile->type == TILE::FLOOR) || (tile->type == TILE::FLOOR_ALT));
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(const Tile& tile)
{
	return ((tile.type == TILE::FLOOR) || (tile.type == TILE::FLOOR_ALT));
}

// Gets the size of the tiles in the level.
int Level::GetTileSize() const
{
	return TILE_SIZE;
}

// Gets a vector of all torches in the level.
std::vector<std::shared_ptr<Torch>>* Level::GetTorches()
{
	return &m_torches;
}

// Draws the level grid to the given render window.
void Level::Draw(sf::RenderWindow& window, float timeDelta)
{
	// Draw the level tiles.
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			window.draw(m_grid[i][j].sprite);
		}
	}

	// Draw all torches.
	for (auto& torch : m_torches)
	{
		torch->Draw(window, timeDelta);
	}
}