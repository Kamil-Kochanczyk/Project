#pragma once

#include "Game.h"

class ReactionTime : public Game
{
public:
	// Constructor and destructor
	ReactionTime();
	~ReactionTime();

	// Functions implementing logic of the game
	void ShowInfoAboutGame();
	void Play();
};
