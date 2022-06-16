#include "AimTrainer.h"
#include <numeric>

AimTrainer::AimTrainer() : Game("Aim Trainer")
{

}

AimTrainer::~AimTrainer()
{

}

void AimTrainer::ShowInfoAboutGame()
{
	std::cout << "Hit all targets as fast as you can\n";
	std::cout << "- run the game from the menu\n";
	std::cout << "- click the target in the middle to start the game\n";
	std::cout << "- hit all targets\n";
	std::cout << "- your average reactions time per target will be displayed in the console\n";
	std::cout << "- after you hit all the targets you can press the right button to play again\n";
}

void AimTrainer::Play()
{
	unsigned int windowWidth = gameWindowWidth;
	unsigned int windowHeight = gameWindowHeight;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Close);

	sf::Texture targetTexture;
	targetTexture.loadFromFile("Target Texture.png");

	float radius = windowHeight * 0.085f;
	sf::CircleShape target(radius);
	target.setTexture(&targetTexture);
	target.setOrigin(radius, radius);
	target.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

	sf::Clock reactionClock;
	std::vector<int> reactionTimes;

	int totalTargets = 30;
	int remainingTargets = totalTargets;

	std::string remaining = "Remaining: ";
	remaining.append(std::to_string(totalTargets));

	sf::Font font;
	font.loadFromFile("Roboto-Regular.ttf");

	sf::Text text(remaining, font);
	text.setCharacterSize((unsigned int)(radius / 2.0f));
	text.setPosition((windowWidth / 2.0f) - (text.getLocalBounds().width / 2.0f), windowHeight - (1.5f * radius));

	bool gameStarted = false;
	bool blackScreen = false;

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
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Right && blackScreen)
			{
				target.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
				reactionTimes.clear();
				remainingTargets = totalTargets;

				blackScreen = false;
			}
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && !blackScreen)
			{
				int xCursorPosition = windowEvent.mouseButton.x;
				int yCursorPosition = windowEvent.mouseButton.y;

				float xTargetPosition = target.getPosition().x;
				float yTargetPosition = target.getPosition().y;

				float distance = sqrt(pow(xCursorPosition - xTargetPosition, 2) + pow(yCursorPosition - yTargetPosition, 2));

				if (distance <= radius)
				{
					if (!gameStarted)
					{
						gameStarted = true;
					}
					else
					{
						reactionTimes.push_back(reactionClock.getElapsedTime().asMilliseconds());
						remainingTargets--;

						if (remainingTargets == 0)
						{
							int averageReactionTime = std::accumulate(reactionTimes.begin(), reactionTimes.end(), 0) / reactionTimes.size();
							std::cout << "Aim Trainer: " << averageReactionTime << " ms\n\n";

							gameStarted = false;
							blackScreen = true;
						}
					}

					if (gameStarted)
					{
						float xRandomPosition = (rand() % (int)(windowWidth - (2 * radius) + 1)) + radius;
						float yRandomPosition = (rand() % (int)(windowHeight - (3.5f * radius) + 1)) + radius;
						target.setPosition(xRandomPosition, yRandomPosition);

						reactionClock.restart();
					}

					remaining = "Remaining: ";
					remaining.append(std::to_string(remainingTargets));
					text.setString(remaining);
				}
			}
		}

		window.clear();
		if (gameStarted) window.draw(text);
		if (!blackScreen) window.draw(target);
		window.display();
	}
}
