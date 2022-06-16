#pragma once

#include "Game.h"

class AimTrainer : public Game
{
public:
	// Constructor and destructor
	AimTrainer();
	~AimTrainer();

	// Functions implementing logic of the game
	void ShowInfoAboutGame();
	void Play();
};
