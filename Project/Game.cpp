#include "Game.h"

const unsigned int Game::gameWindowWidth = (unsigned int)(sf::VideoMode::getDesktopMode().width / 1.5);
const unsigned int Game::gameWindowHeight = (unsigned int)(sf::VideoMode::getDesktopMode().height / 1.5);

Game::Game(std::string title) : title(title)
{

}

Game::~Game()
{

}

std::string Game::GetTitle() const
{
	return title;
}
