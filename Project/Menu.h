#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>

class Game;

class Menu
{
private:
	sf::RenderWindow& window;	// Menu will be displayed in this window
	std::vector<Game*> games;	// These games will be available in the menu
	unsigned int numberOfGames;	// Size of the vector above
	unsigned int activeGame;	// Index of currently highlighted game

public:
	// Constructor and desctructor
	Menu(sf::RenderWindow& window, std::vector<Game*> games);
	~Menu();

	// Getters
	std::vector<Game*> GetGames() const;
	unsigned int GetNumberOfGames() const;
	unsigned int GetActiveGame() const;

	// Functions implementing logic of the menu
	void ShowInfoAboutMenu();
	void ShowMenu();
	void ChooseGame(sf::Event arrowPressed);

public:
	Menu operator+=(Game* game);	// Operator adding a chosen game to the menu
	Menu operator-=(Game* game);	// Operator removing a chosen game from the menu
};
