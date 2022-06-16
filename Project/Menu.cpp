#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, std::vector<Game*> games) : window(window), games(games), numberOfGames(games.size()), activeGame(0)
{
	if (numberOfGames <= 0)
	{
		throw std::exception("There has to be at least one game in the menu");
	}

	if (numberOfGames > 8)
	{
		throw std::exception("Number of games in the menu cannot be grater than 8");
	}
}

Menu::~Menu()
{

}

std::vector<Game*> Menu::GetGames() const
{
	return games;
}

unsigned int Menu::GetNumberOfGames() const
{
	return numberOfGames;
}

unsigned int Menu::GetActiveGame() const
{
	return activeGame;
}

void Menu::ShowInfoAboutMenu()
{
	std::cout << "Test your skills with these brain games!\n";
	std::cout << "To play original games, visit https://humanbenchmark.com/\n";
	std::cout << "Use up and down arrow keys to choose a game from the menu\n";
	std::cout << "Press enter to play the chosen game\n";
	std::cout << "Press escape to quit\n";
}

void Menu::ShowMenu()
{
	window.clear(sf::Color::Black);

	sf::Font font;
	font.loadFromFile("Roboto-Regular.ttf");

	for (unsigned int i = 0; i < numberOfGames; i++)
	{
		sf::Text gameText(games[i]->title, font);

		if (i == activeGame)
		{
			gameText.setFillColor(sf::Color::Cyan);
		}
		else
		{
			gameText.setFillColor(sf::Color::White);
		}

		gameText.setCharacterSize(window.getSize().y / (numberOfGames + 2) / 2);
		
		float gameTextPositionX = (window.getSize().x / 2.0f) - (gameText.getLocalBounds().width / 2.0f);
		float gameTextPositionY = gameText.getCharacterSize() * 2 * (i + 1);
		gameText.setPosition(gameTextPositionX, gameTextPositionY);

		window.draw(gameText);
	}

	window.display();
}

void Menu::ChooseGame(sf::Event arrowPressed)
{
	if (arrowPressed.type == sf::Event::KeyPressed)
	{
		switch (arrowPressed.key.code)
		{
		case sf::Keyboard::Key::Up:
			activeGame = (activeGame == 0) ? (numberOfGames - 1) : (activeGame - 1);
			break;
		case sf::Keyboard::Key::Down:
			activeGame = (activeGame == (numberOfGames - 1)) ? 0 : (activeGame + 1);
			break;
		case sf::Keyboard::Key::Enter:
			window.setVisible(false);
			games[activeGame]->Play();
			window.setVisible(true);
			break;
		case sf::Keyboard::Key::Escape:
			window.close();
		}

		ShowMenu();
	}
}

Menu Menu::operator+=(Game* game)
{
	this->games.push_back(game);
	(this->numberOfGames)++;

	if ((this->numberOfGames) > 8)
	{
		throw std::exception("Number of games in the menu cannot be grater than 8");
	}

	return *this;
}

Menu Menu::operator-=(Game* game)
{
	auto iterator = std::find(this->games.begin(), this->games.end(), game);

	if (iterator != this->games.end())
	{
		this->games.erase(iterator);
		(this->numberOfGames)--;
	}

	if (numberOfGames <= 0)
	{
		throw std::exception("There has to be at least one game in the menu");
	}

	return *this;
}
