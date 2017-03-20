/**
 * @file src\game.cpp
 *
 * Implements the game class.
 */

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <glm/glm.hpp>
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
	return m_clock.getElapsedTime();
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
	m_lastUpdateTime = m_clock.getElapsedTime();
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
	return m_ended;
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
	return  m_clock.getElapsedTime() - m_lastUpdateTime;
}

sf::Texture *Game::LoadTexture(std::string filename)
{
	sf::Texture *tex;
	if (m_textures.find(filename) != m_textures.end())
	{
		return m_textures[filename];
	}
	else
	{
		tex = new sf::Texture();
		tex->loadFromFile(filename);
		m_textures[filename] = tex;
		return tex;
	}
}

glm::vec2 Game::Screen()
{
	return m_screen;
}

sf::Shader *LoadShader(std::string name, std::string vert_file, std::string frag_file)
{

}


sf::Shader *Game::Shader(std::string name)
{
	std::map<std::string, Shader*>::iterator it;
	if ((it = m_shaders.find(name)) != m_shaders.end())
	{
		return it.second;
	}
	else
		return NULL;
}