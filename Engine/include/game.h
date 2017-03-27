/**************************************************************************************************/
/**
 * @file	include\game.h.
 *
 * @brief	Declares the game class.
 **************************************************************************************************/
#pragma once
#include "entity.h"
#include "shader.h"
#include "sprite.h"
#include "ui.h"
#include "scripts.h"
#include "actor.h"



#define STARTING_MAX_ENTITIES 100

/**************************************************************************************************/
/**
 * @class	Game
 *
 * @brief	A game.
 *
 * @author	Aimle
 * @date	3/25/2017
 **************************************************************************************************/
class Game
{
	sf::Clock m_clock;  /**< The clock */
	sf::Window m_window;	/**< The window */
	bool m_ended;   /**< True if ended */
	sf::Time m_lastUpdateTime;  /**< The last update time */
	std::vector<Entity> m_entities; /**< The entities */
	std::map<std::string, sf::Texture*> m_textures; /**< The textures */
	std::map<std::string, Shader*> m_shaders;   /**< The shaders */
	Shader *m_currentShader; /**< The current shader */
	glm::mat4 m_modelMatrix;	/**< The model matrix */
	glm::mat4 m_projectionMatrix;   /**< The projection matrix */
	glm::mat4 m_viewMatrix; /**< The view matrix */
	glm::mat4 m_MVP;	/**< The mvp */
	glm::vec2 m_screen; /**< The screen */
	glm::vec3 m_cameraPosition; /**< The camera position */
	glm::vec3 m_cameraRotation; /**< The camera rotation */
	sf::ContextSettings m_contextSettings;  /**< The context settings */
	GLuint m_vbo;
	GLuint m_UVbo;

public:

	/**************************************************************************************************/
	/**
	 * @fn	sf::Time Game::Time();
	 *
	 * @brief	Gets the time.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	A sf::Time.
	 **************************************************************************************************/
	sf::Time Time();

	/**************************************************************************************************/
	/**
	 * @fn	Game::Game();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	Game();

	/**************************************************************************************************/
	/**
	 * @fn	void Game::Startup();
	 *
	 * @brief	Prepares this object for use.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	void Startup();

	/**************************************************************************************************/
	/**
	 * @fn	void Game::Input();
	 *
	 * @brief	Inputs this object.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	void Input();

	/**************************************************************************************************/
	/**
	 * @fn	void Game::Update();
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	void Update();

	/**************************************************************************************************/
	/**
	 * @fn	void Game::Draw();
	 *
	 * @brief	Draws this object.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	void Draw();

	/**************************************************************************************************/
	/**
	 * @fn	void Game::Shutdown();
	 *
	 * @brief	Shuts down this object and frees any resources it is using.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	void Shutdown();

	/**************************************************************************************************/
	/**
	 * @fn	sf::Texture Game::*LoadTexture(std::string filename);
	 *
	 * @brief	Loads a texture.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	Null if it fails, else the texture.
	 **************************************************************************************************/
	sf::Texture *LoadTexture(std::string filename);

	/**************************************************************************************************/
	/**
	 * @fn	Shader Game::*LoadShader(std::string name, std::string vert_file, std::string frag_file);
	 *
	 * @brief	Loads a shader.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	name	 	The name.
	 * @param	vert_file	The vertical file.
	 * @param	frag_file	The fragment file.
	 *
	 * @return	Null if it fails, else the shader.
	 **************************************************************************************************/
	Shader *LoadShader(std::string name, std::string vert_file, std::string frag_file);

	/**************************************************************************************************/
	/**
	 * @fn	Shader Game::*GetShader(std::string name);
	 *
	 * @brief	Gets a shader.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	name	The name.
	 *
	 * @return	Null if it fails, else the shader.
	 **************************************************************************************************/
	Shader *GetShader(std::string name);

	/**************************************************************************************************/
	/**
	 * @fn	void Game::UseShader(std::string name);
	 *
	 * @brief	Use shader.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	name	The name.
	 **************************************************************************************************/
	void UseShader(std::string name);

	/**************************************************************************************************/
	/**
	 * @fn	void Game::TranslateCamera(glm::vec3 vector);
	 *
	 * @brief	Translate camera.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	vector	The vector.
	 **************************************************************************************************/
	void TranslateCamera(glm::vec3 vector);

	/**************************************************************************************************/
	/**
	 * @fn	void Game::RotateCamera(glm::vec3 vector);
	 *
	 * @brief	Rotate camera.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	vector	The vector.
	 **************************************************************************************************/
	void RotateCamera(glm::vec3 vector);

	/**************************************************************************************************/
	/**
	 * @fn	void Game::SetCameraRotation(glm::vec3 vector);
	 *
	 * @brief	Sets camera rotation.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	vector	The vector.
	 **************************************************************************************************/
	void Game::SetCameraRotation(glm::vec3 vector);

	/**************************************************************************************************/
	/**
	 * @fn	bool Game::Ended();
	 *
	 * @brief	Ended this object.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/
	bool Ended();

	/**************************************************************************************************/
	/**
	 * @fn	sf::Time Game::Delta();
	 *
	 * @brief	Gets the delta.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	A sf::Time.
	 **************************************************************************************************/
	sf::Time Delta();

	/**************************************************************************************************/
	/**
	 * @fn	glm::vec2 Game::Screen();
	 *
	 * @brief	Gets the screen.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	A glm::vec2.
	 **************************************************************************************************/
	glm::vec2 Screen();

	/**************************************************************************************************/
	/**
	 * @fn	Entity Game::*NewEntity();
	 *
	 * @brief	Gets new entity.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @return	Null if it fails, else the new entity.
	 **************************************************************************************************/
	Entity *NewEntity();

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Game::Vbo();
	 *
	 * @brief	Gets the vbo.
	 *
	 * @author	Bo Thompson
	 * @date	3/27/2017
	 *
	 * @return	A GLuint.
	 **************************************************************************************************/
	GLuint Vbo();

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Game::UVbo();
	 *
	 * @brief	Gets the uvbo.
	 *
	 * @author	Bo Thompson
	 * @date	3/27/2017
	 *
	 * @return	A GLuint.
	 **************************************************************************************************/
	GLuint UVbo();
};

extern Game *game;  /**< The game */