#pragma once

#include "Game.h"

class SequenceMemory : public Game
{
public:
	// Constructor and destructor
	SequenceMemory();
	~SequenceMemory();

	// Functions implementing logic of the game
	void ShowInfoAboutGame();
	void Play();

private:
	// Auxiliary function
	void ShowInterface(sf::RenderWindow& window, std::vector<sf::RectangleShape>& tiles, sf::Text& scoreText);
};
