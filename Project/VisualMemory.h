#pragma once

#include "Game.h"

class VisualMemory : public Game
{
public:
	// Constructor and destructor
	VisualMemory();
	~VisualMemory();

	// Functions implementing logic of the game
	void ShowInfoAboutGame();
	void Play();

private:
	// Auxiliary functions
	void SetUpGrid(sf::RenderWindow& window, unsigned int tilesPerRow, unsigned int tilesPerColumn, std::vector<sf::RectangleShape>& tiles);
	void DrawAndWait(sf::RenderWindow& window, std::vector<sf::RectangleShape>& tiles, sf::Text& levelText, sf::Text& livesText, bool gameRunning, unsigned int time);
	void SetLevelTextPosition(sf::Text& levelText, std::vector<sf::RectangleShape>& tiles, sf::RenderWindow& window);
	void SetLivesTextPosition(sf::Text& livesText, std::vector<sf::RectangleShape>& tiles, sf::RenderWindow& window);
};
