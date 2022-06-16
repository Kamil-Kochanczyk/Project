#include "VisualMemory.h"
#include <numeric>

VisualMemory::VisualMemory() : Game("Visual Memory")
{

}

VisualMemory::~VisualMemory()
{

}

void VisualMemory::ShowInfoAboutGame()
{
	std::cout << "Memorize the pattern and then recreate it\n";
	std::cout << "- run the game from the menu\n";
	std::cout << "- click to start\n";
	std::cout << "- click the correct tiles to recreate the pattern\n";
	std::cout << "- if you make three mistakes in a level, you will lose one life\n";
	std::cout << "- the last level that you reached will be displayed in the console as your score\n";
}

void VisualMemory::Play()
{
	srand(time(0));

	unsigned int windowWidth = gameWindowWidth;
	unsigned int windowHeight = gameWindowHeight;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Close);

	unsigned int tilesPerRow = 3;
	unsigned int tilesPerColumn = tilesPerRow;
	std::vector<sf::RectangleShape> tiles;

	SetUpGrid(window, tilesPerRow, tilesPerColumn, tiles);

	unsigned int lastLevel = 25;
	unsigned int level;
	unsigned int lives;
	unsigned int errorsPerLevel;
	unsigned int tilesInPattern;
	unsigned int clickedTile = -1;	// Default value -1 means that no tile has been clicked

	std::vector<int> candidates;
	std::vector<int> pattern;
	std::vector<int> recreated;

	sf::Font font;
	font.loadFromFile("Roboto-Regular.ttf");

	std::string levelString = "Level: 1";
	sf::Text levelText(levelString, font);
	levelText.setCharacterSize(windowHeight / 15.0f);
	SetLevelTextPosition(levelText, tiles, window);

	std::string livesString = "Lives: 3";
	sf::Text livesText(livesString, font);
	livesText.setCharacterSize(levelText.getCharacterSize());
	SetLivesTextPosition(livesText, tiles, window);

	bool gameRunning = false;
	bool initializingPattern = false;
	bool showingPattern = false;
	bool playerRecreating = false;

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

				level = 1;
				lives = 3;
				errorsPerLevel = 0;
				tilesInPattern = 3;
				clickedTile = -1;

				levelString = "Level: 1";
				levelText.setString(levelString);

				livesString = "Lives: 3";
				livesText.setString(livesString);

				initializingPattern = true;
			}
			else if (windowEvent.type == sf::Event::MouseButtonPressed && windowEvent.mouseButton.button == sf::Mouse::Button::Left && playerRecreating)
			{
				int xCursorPosition = windowEvent.mouseButton.x;
				int yCursorPosition = windowEvent.mouseButton.y;

				for (int i = 0; i < tiles.size(); i++)
				{
					float leftBound = tiles[i].getPosition().x;
					float rightBound = tiles[i].getPosition().x + tiles[i].getSize().x;
					float upBound = tiles[i].getPosition().y;
					float downBound = tiles[i].getPosition().y + tiles[i].getSize().y;

					if (xCursorPosition >= leftBound && xCursorPosition <= rightBound)
					{
						if (yCursorPosition >= upBound && yCursorPosition <= downBound)
						{
							clickedTile = i;
							break;
						}
					}
				}
			}
		}

		if (clickedTile != -1)
		{
			auto patternIterator = std::find(pattern.begin(), pattern.end(), clickedTile);
			auto recreatedIterator = std::find(recreated.begin(), recreated.end(), clickedTile);

			bool correctTileClicked = (patternIterator != pattern.end()) || (recreatedIterator != recreated.end());

			if (correctTileClicked)
			{
				tiles[clickedTile].setFillColor(sf::Color::Green);

				if (patternIterator != pattern.end())
				{
					recreated.push_back(*(patternIterator));
					pattern.erase(patternIterator);
				}

				if (pattern.empty())
				{
					DrawAndWait(window, tiles, levelText, livesText, gameRunning, 350);

					switch (level)
					{
						case 2:
						case 5:
						case 8:
						case 13:
						case 19:
							tilesPerRow++;
							break;
					}

					if (level == lastLevel)
					{
						tilesPerRow = 3;
					}

					tilesPerColumn = tilesPerRow;

					level++;
					errorsPerLevel = 0;
					tilesInPattern++;

					levelString = "Level: ";
					levelString.append(std::to_string(level));
					levelText.setString(levelString);

					recreated.resize(0);

					SetUpGrid(window, tilesPerRow, tilesPerColumn, tiles);
					SetLevelTextPosition(levelText, tiles, window);
					SetLivesTextPosition(livesText, tiles, window);
					DrawAndWait(window, tiles, levelText, livesText, gameRunning, 350);

					playerRecreating = false;
					initializingPattern = true;

					if (level == lastLevel + 1)
					{
						std::cout << "Congratulations! You passed all " << lastLevel << " levels! You have an amazing memory!\n\n";
						gameRunning = false;
						initializingPattern = false;
					}
				}
			}
			else
			{
				if (tiles[clickedTile].getFillColor() != sf::Color::Red)
				{
					tiles[clickedTile].setFillColor(sf::Color::Red);

					errorsPerLevel++;

					if (errorsPerLevel == 3)
					{
						lives--;
						errorsPerLevel = 0;

						livesString = "Lives: ";
						livesString.append(std::to_string(lives));
						livesText.setString(livesString);

						DrawAndWait(window, tiles, levelText, livesText, gameRunning, 350);

						if (lives != 0)
						{
							initializingPattern = true;
						}

						playerRecreating = false;
					}

					if (lives == 0)
					{
						std::cout << "Visual Memory: " << level << "\n\n";

						tilesPerRow = 3;
						tilesPerColumn = tilesPerRow;
						SetUpGrid(window, tilesPerRow, tilesPerColumn, tiles);

						SetLevelTextPosition(levelText, tiles, window);
						SetLivesTextPosition(livesText, tiles, window);

						gameRunning = false;
						playerRecreating = false;
					}
				}
			}

			clickedTile = -1;
		}

		if (initializingPattern)
		{
			candidates.resize(tiles.size());
			std::iota(candidates.begin(), candidates.end(), 0);

			pattern.resize(0);

			int randomTile;
			for (int i = 1; i <= tilesInPattern; i++)
			{
				randomTile = rand() % candidates.size();
				pattern.push_back(candidates[randomTile]);
				candidates.erase(candidates.begin() + randomTile);
			}

			initializingPattern = false;
			showingPattern = true;
		}

		if (showingPattern)
		{
			for (int i = 0; i < tiles.size(); i++)
			{
				if (std::find(pattern.begin(), pattern.end(), i) != pattern.end())
				{
					tiles[i].setFillColor(sf::Color::Blue);
				}
			}

			DrawAndWait(window, tiles, levelText, livesText, gameRunning, 1500);

			showingPattern = false;
			playerRecreating = true;
		}

		window.clear();
		for (const auto& tile : tiles)
		{
			window.draw(tile);
		}
		if (gameRunning)
		{
			window.draw(levelText);
			window.draw(livesText);
		}
		window.display();
	}
}

void VisualMemory::SetUpGrid(sf::RenderWindow& window, unsigned int tilesPerRow, unsigned int tilesPerColumn, std::vector<sf::RectangleShape>& tiles)
{
	tiles.clear();

	unsigned int windowWidth = window.getSize().x;
	unsigned int windowHeight = window.getSize().y;
	float halfWidth = windowWidth / 2.0f;
	float halfHeight = windowHeight / 2.0f;

	float tileSize = windowHeight / (tilesPerRow + 2.0f);
	float halfSize = tileSize / 2.0f;
	float spacing = (1.0f / 7.0f) * tileSize;

	sf::Vector2f upperLeftCorner;
	upperLeftCorner.x = halfWidth - (tilesPerColumn * halfSize) - (((tilesPerColumn - 1.0f) / 2.0f) * spacing);
	upperLeftCorner.y = halfHeight - (tilesPerRow * halfSize) - (((tilesPerRow - 1.0f) / 2.0f) * spacing);

	if (tilesPerColumn % 2 == 0)
	{
		upperLeftCorner.x -= 0.5f * spacing;
	}
	if (tilesPerRow % 2 == 0)
	{
		upperLeftCorner.y -= 0.5f * spacing;
	}

	sf::Vector2f shift;
	int index;

	for (int i = 0; i < tilesPerRow; i++)
	{
		shift.y = i * (tileSize + spacing);

		for (int j = 0; j < tilesPerColumn; j++)
		{
			shift.x = j * (tileSize + spacing);

			tiles.push_back(sf::RectangleShape(sf::Vector2f(tileSize, tileSize)));

			index = (i * tilesPerColumn) + j;
			tiles[index].setPosition(upperLeftCorner + shift);
		}
	}
}

void VisualMemory::DrawAndWait(sf::RenderWindow& window, std::vector<sf::RectangleShape>& tiles, sf::Text& levelText, sf::Text& livesText, bool gameRunning, unsigned int time)
{
	window.clear();
	for (const auto& tile : tiles)
	{
		window.draw(tile);
	}
	if (gameRunning)
	{
		window.draw(levelText);
		window.draw(livesText);
	}
	window.display();

	sf::Clock waitClock;
	while (waitClock.getElapsedTime().asMilliseconds() <= time);

	sf::Event eventToSkip;
	while (window.pollEvent(eventToSkip));

	for (auto& tile : tiles)
	{
		tile.setFillColor(sf::Color::White);
	}
}

void VisualMemory::SetLevelTextPosition(sf::Text& levelText, std::vector<sf::RectangleShape>& tiles, sf::RenderWindow& window)
{
	unsigned int windowWidth = window.getSize().x;
	unsigned int windowHeight = window.getSize().y;

	float levelOriginX = tiles[0].getPosition().x / 2.0f;
	float levelShiftX = levelText.getLocalBounds().width / 2.0f;
	float levelOriginY = windowHeight / 2.0f;
	float levelShiftY = levelText.getLocalBounds().height / 2.0f;

	levelText.setPosition(levelOriginX - levelShiftX, levelOriginY - levelShiftY);
}

void VisualMemory::SetLivesTextPosition(sf::Text& livesText, std::vector<sf::RectangleShape>& tiles, sf::RenderWindow& window)
{
	unsigned int windowWidth = window.getSize().x;
	unsigned int windowHeight = window.getSize().y;

	float livesOriginX = tiles[tiles.size() - 1].getPosition().x + tiles[tiles.size() - 1].getSize().x;
	livesOriginX = (livesOriginX + windowWidth) / 2.0f;
	float livesShiftX = livesText.getLocalBounds().width / 2.0f;
	float livesOriginY = windowHeight / 2.0f;
	float livesShiftY = livesText.getLocalBounds().height / 2.0f;

	livesText.setPosition(livesOriginX - livesShiftX, livesOriginY - livesShiftY);
}
