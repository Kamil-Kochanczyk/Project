#include "Game.h"
#include "ReactionTime.h"
#include "SequenceMemory.h"
#include "AimTrainer.h"
#include "VisualMemory.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(Game::gameWindowWidth, Game::gameWindowHeight), "Brain Games", sf::Style::Close);

	Game* reactionTime = new ReactionTime;
	Game* sequenceMemory = new SequenceMemory;
	Game* aimTrainer = new AimTrainer;
	Game* visualMemory = new VisualMemory;

	std::array<Game*, 3> gamesArray = { reactionTime, sequenceMemory, aimTrainer };
	std::vector<Game*> games(gamesArray.begin(), gamesArray.end());

	try
	{
		Menu menu(window, games);

		menu += visualMemory;

		menu.ShowInfoAboutMenu();
		std::cout << std::endl << std::endl;

		for (const auto game : menu.GetGames())
		{
			std::cout << game->GetTitle() << ":" << std::endl;
			game->ShowInfoAboutGame();
			std::cout << std::endl << std::endl;
		}

		menu.ShowMenu();

		while (window.isOpen())
		{
			sf::Event windowEvent;

			while (window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (windowEvent.type == sf::Event::KeyPressed)
				{
					menu.ChooseGame(windowEvent);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	delete reactionTime;
	delete sequenceMemory;
	delete aimTrainer;
	delete visualMemory;

	return 0;
}
