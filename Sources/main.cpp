#include "PCH.h"
#include "Game.h"

// Entry point of the application.
int main()
{
	// Set a random seed.
	srand(42);

	// Create the main game object.
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Roguelike Template", sf::Style::Fullscreen);
	Game game(&window);

	// Initialize and run the game object.
	game.Initialize();
	game.Run();

	// Exit the application.
	return 0;
}