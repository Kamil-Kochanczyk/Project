#include "ReactionTime.h"

ReactionTime::ReactionTime() : Game("Reaction Time")
{

}

ReactionTime::~ReactionTime()
{

}

void ReactionTime::ShowInfoAboutGame()
{
	std::cout << "This game measures your reaction time\n";
	std::cout << "- run the game from the menu\n";
	std::cout << "- click to start\n";
	std::cout << "- wait until the window turns green and click again as quickly as possible\n";
	std::cout << "- your reaction time will be displayed in the console\n";
}

void ReactionTime::Play()
{
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(gameWindowWidth, gameWindowHeight), title, sf::Style::Close);

	sf::RectangleShape clickArea(sf::Vector2f(window.getSize().x, window.getSize().y));
	clickArea.setFillColor(sf::Color::Black);

	bool isBlack = true;
	bool isRed = false;
	bool isGreen = false;

	sf::Clock sleepClock;
	sf::Clock reactionClock;

	int sleepTime = rand() % 4001 + 2000;	// Random time from 2000ms to 6000ms
	int reactionTime;

	while (window.isOpen())
	{
		sf::Event windowEvent;

		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (windowEvent.type == sf::Event::KeyPressed && windowEvent.key.code == sf::Keyboard::Key::Escape)
			{
				window.close();
			}
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && isBlack)
			{
				isBlack = false;
				isRed = true;
				clickArea.setFillColor(sf::Color::Red);
				sleepClock.restart();
			}
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && isRed)
			{
				isRed = false;
				isBlack = true;
				clickArea.setFillColor(sf::Color::Black);
				std::cout << "You clicked too early!\n\n";
			}
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && isGreen)
			{
				reactionTime = reactionClock.getElapsedTime().asMilliseconds();
				std::cout << "Reaction Time: " << reactionTime << " ms\n\n";

				isGreen = false;
				isBlack = true;
				clickArea.setFillColor(sf::Color::Black);
			}
		}

		if (isRed)
		{
			if (sleepClock.getElapsedTime().asMilliseconds() >= sleepTime)
			{
				isRed = false;
				isGreen = true;
				clickArea.setFillColor(sf::Color::Green);
				reactionClock.restart();
			}
		}

		window.clear();
		window.draw(clickArea);
		window.display();
	}
}
