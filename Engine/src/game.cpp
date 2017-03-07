/**
 * @file src\game.cpp
 *
 * Implements the game class.
 */

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "game.h"

/**
 * Gets the time.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 *
 * @return A sf::Time.
 */

sf::Time Game::Time()
{
	return _clock.getElapsedTime();
}

/**
 * Default constructor.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 */

Game::Game()
{

}

/**
 * Prepares the game.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 */

void Game::Startup()
{

}

/**
 * Gets input for the game.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 */

void Game::Input()
{

}

/**
 * Draws the game.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 */

void Game::Draw()
{

}

/**
 * Updates the game.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 */

void Game::Update()
{
	_lastUpdateTime = _clock.getElapsedTime();
}

/**
 * Shuts down this game and frees any resources it is using.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 */

void Game::Shutdown()
{

}

/**
 * Has this game been marked finished
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 *
 * @return True if it succeeds, false if it fails.
 */

bool Game::Ended()
{
	return _ended;
}

/**
 * Gets the delta.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 *
 * @return A sf::Time.
 */

sf::Time Game::Delta()
{
	return  _clock.getElapsedTime() - _lastUpdateTime;
}

sf::Texture *Game::LoadTexture(std::string filename)
{
	sf::Texture *tex;
	if (_textures.find(filename) != _textures.end())
	{
		return _textures[filename];
	}
	else
	{
		tex = new sf::Texture();
		tex->loadFromFile(filename);
		_textures[filename] = tex;
		return tex;
	}
}