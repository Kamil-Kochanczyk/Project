#include "SequenceMemory.h"

SequenceMemory::SequenceMemory() : Game("Sequence Memory")
{

}

SequenceMemory::~SequenceMemory()
{

}

void SequenceMemory::ShowInfoAboutGame()
{
	std::cout << "Memorize the pattern and then repeat it by clicking tiles in the correct order\n";
	std::cout << "- run the game from the menu\n";
	std::cout << "- click to start\n";
	std::cout << "- try to memorize the pattern and repeat it\n";
	std::cout << "- the number of tiles that you managed to memorize tiles will be displayed in the console\n";
	std::cout << "- WARNING - during animations the game window becomes unresponsive\n";
}

void SequenceMemory::Play()
{
	srand(time(0));

	unsigned int windowWidth = gameWindowWidth;
	unsigned int windowHeight = gameWindowHeight;
	float halfWidth = windowWidth / 2.0f;
	float halfHeight = windowHeight / 2.0f;
	float tileSize = windowHeight / 5.0f;
	float coefficient = (8.0f / 7.0f) * tileSize;	// (coefficient = 8/7 * tileSize) => (spacing between tiles = 1/7 * tileSize)

	std::vector<sf::RectangleShape> tiles;

	for (int i = 0; i < 9; i++)
	{
		tiles.push_back(sf::RectangleShape(sf::Vector2f(tileSize, tileSize)));
		tiles[i].setOrigin(tiles[i].getSize().x / 2.0f, tiles[i].getSize().y / 2.0f);
	}

	tiles[0].setPosition(halfWidth - coefficient, halfHeight - coefficient);
	tiles[1].setPosition(halfWidth, halfHeight - coefficient);
	tiles[2].setPosition(halfWidth + coefficient, halfHeight - coefficient);
	tiles[3].setPosition(halfWidth - coefficient, halfHeight);
	tiles[4].setPosition(halfWidth, halfHeight);
	tiles[5].setPosition(halfWidth + coefficient, halfHeight);
	tiles[6].setPosition(halfWidth - coefficient, halfHeight + coefficient);
	tiles[7].setPosition(halfWidth, halfHeight + coefficient);
	tiles[8].setPosition(halfWidth + coefficient, halfHeight + coefficient);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Close);

	std::vector<int> tileSequence;
	int currentTileInSequence;	// More accurately - INDEX of current tile in sequence
	int clickedTile;	// More accurately - INDEX of clicked tile, value -1 means that no tile has been clicked yet

	int score = 0;

	std::string scoreString = "Score: 0";
	
	sf::Font font;
	font.loadFromFile("Roboto-Regular.ttf");
	
	sf::Text scoreText(scoreString, font);
	scoreText.setCharacterSize((unsigned int)(tileSize / 3.0f));
	scoreText.setPosition(halfWidth - (scoreText.getLocalBounds().width / 2.0f), halfHeight + (2.0f * tileSize));

	bool gameRunning = false;
	bool animationPlaying = false;
	bool repeating = false;

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
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && !gameRunning)
			{
				gameRunning = true;

				tileSequence.clear();
				tileSequence.push_back(rand() % 9);

				currentTileInSequence = 0;
				clickedTile = -1;

				score = 0;
				scoreString = "Score: 0";
				scoreText.setString(scoreString);

				animationPlaying = true;
			}
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && repeating)
			{
				int xCursorPosition = windowEvent.mouseButton.x;
				int yCursorPosition = windowEvent.mouseButton.y;
				float halfSize = tileSize / 2.0f;

				for (int i = 0; i < 9; i++)
				{
					float leftBound = tiles[i].getPosition().x - halfSize;
					float rightBound = tiles[i].getPosition().x + halfSize;
					float upBound = tiles[i].getPosition().y - halfSize;
					float downBound = tiles[i].getPosition().y + halfSize;

					if (xCursorPosition >= leftBound && xCursorPosition <= rightBound)
					{
						if (yCursorPosition >= upBound && yCursorPosition <= downBound)
						{
							clickedTile = i;
							break;
						}
					}
				}

				if (clickedTile != -1)
				{
					if (clickedTile == tileSequence[currentTileInSequence])
					{
						tiles[clickedTile].setFillColor(sf::Color::Green);
						currentTileInSequence++;

						if (currentTileInSequence == tileSequence.size())
						{
							score++;
							tileSequence.push_back(rand() % 9);
							currentTileInSequence = 0;

							repeating = false;
							animationPlaying = true;
						}
					}
					else
					{
						tiles[clickedTile].setFillColor(sf::Color::Red);
						std::cout << "Sequence Memory: " << score << "\n\n";
						score = 0;

						repeating = false;
						gameRunning = false;
					}

					ShowInterface(window, tiles, scoreText);

					if (!gameRunning)	// If player clicked the wrong tile, show red color, end the game and wait for click
					{
						sf::Event eventToSkip;
						while (window.pollEvent(eventToSkip));
						while (!window.pollEvent(eventToSkip) || eventToSkip.type != sf::Event::MouseButtonPressed || eventToSkip.mouseButton.button != sf::Mouse::Button::Left);
					}
					else    // If player clicked the correct tile, show green color for a very short amount of time
					{
						sf::Clock waitClock;
						while (waitClock.getElapsedTime().asMilliseconds() <= 100);
					}

					tiles[clickedTile].setFillColor(sf::Color::White);

					if (animationPlaying)	// If player finished the sequence, wait a little bit before starting the next one
					{
						ShowInterface(window, tiles, scoreText);

						sf::Clock waitClock;
						while (waitClock.getElapsedTime().asMilliseconds() <= 500);
					}

					scoreString = "Score: ";
					scoreString.append(std::to_string(score));
					scoreText.setString(scoreString);

					clickedTile = -1;
				}
			}
		}

		if (animationPlaying)
		{
			int highlightTime = 500;
			sf::Clock highlightClock;
			sf::Event eventToSkip;

			for (int index : tileSequence)
			{
				tiles[index].setFillColor(sf::Color::Blue);
				ShowInterface(window, tiles, scoreText);

				highlightClock.restart();
				while (highlightClock.getElapsedTime().asMilliseconds() <= highlightTime);

				tiles[index].setFillColor(sf::Color::White);
				ShowInterface(window, tiles, scoreText);

				highlightClock.restart();
				while (highlightClock.getElapsedTime().asMilliseconds() <= highlightTime);
			}

			while (window.pollEvent(eventToSkip));

			animationPlaying = false;
			repeating = true;
		}

		ShowInterface(window, tiles, scoreText);
	}
}

void SequenceMemory::ShowInterface(sf::RenderWindow& window, std::vector<sf::RectangleShape>& tiles, sf::Text& scoreText)
{
	window.clear();
	for (const auto& tile : tiles) window.draw(tile);
	window.draw(scoreText);
	window.display();
}
