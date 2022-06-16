#pragma once

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu;

class Game
{
	friend class Menu;	// Menu can now access all properties of games to display and run them easily

public:
	static const unsigned int gameWindowWidth;	// Default width
	static const unsigned int gameWindowHeight;	// Default height

protected:
	std::string title;	// Title of a game

public:
	// Constructor and destructor
	Game(std::string title);
	virtual ~Game() = 0;

	// Getter
	std::string GetTitle() const;

	// Functions implementing logic a game
	virtual void ShowInfoAboutGame() = 0;
	virtual void Play() = 0;
};
