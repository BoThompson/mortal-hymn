/**************************************************************************************************/
/**
 * @file	include\game.h.
 *
 * @brief	Declares the game class.
 **************************************************************************************************/
#pragma once
#include <json.hpp>
using json = nlohmann::json;


#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <SFML\graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <vector>
#include <array>
#include <assimp\Importer.hpp>
#include <assimp\mesh.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "shader.h"
#include "texture.h"
#include "postprocess.h"
#include "mesh.h"
#include "animation.h"
#include "model.h"
#include "entity.h"
#include "animation.h"
#include "entity.h"
#include "shader.h"
#include "sprite.h"
#include "ui.h"
#include "healthbar.h"
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
	PostProcess *m_testProcess; /**< The test postprocess */
	PostProcess *m_testProcess2;
	Entity *m_player; /**< The player's entity */
	sf::Clock m_clock;  /**< The clock */
	sf::Window m_window;	/**< The window */
	bool m_ended;   /**< True if ended */
	sf::Time m_lastUpdateTime;  /**< The last update time */
	std::vector<Entity> m_entities; /**< The entities */
	std::map<std::string, PyObject*> m_pyModules; /**< The python modules for actors */
	std::vector<Actor> m_actors; /**< The actors */
	std::map<std::string, Texture*> m_textures; /**< The textures */
	std::map<std::string, Shader*> m_shaders;   /**< The shaders */
	std::map<std::string, Model*> m_models; /**< The models */
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
	short m_process;

public:

	/**************************************************************************************************/
	/**
	 * @fn	Model *Game::LoadModel(std::string filename) sf::Time Time();
	 *
	 * @brief	Loads a model.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	Null if it fails, else the model.
	 **************************************************************************************************/
	Model *LoadModel(std::string filename);

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
	 * @author	Bo Thompson
	 * @date	4/27/2017
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
	 * @fn	Texture Game::*LoadTexture(std::string filename);
	 *
	 * @brief	Loads a texture.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	Null if it fails, else the texture.
	 **************************************************************************************************/
	Texture *LoadTexture(std::string filename);

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
	 * @fn	Shader Game::*GetCurrentShader();
	 *
	 * @brief	Gets current shader.
	 *
	 * @author	Bo Thompson
	 * @date	4/18/2017
	 *
	 * @return	Null if it fails, else the current shader.
	 **************************************************************************************************/
	Shader *GetCurrentShader();

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
	 * @fn	Actor Game::*NewActor();
	 *
	 * @brief	Creates a new actor.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @return	Null if it fails, else a pointer to an Actor.
	 **************************************************************************************************/
	Actor *NewActor();

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

	/**************************************************************************************************/
	/**
	 * @fn	json Game::LoadDictionary(std::string filename);
	 *
	 * @brief	Loads a JSON dictionary.
	 *
	 * @author	Bo Thompson
	 * @date	3/30/2017
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	The dictionary.
	 **************************************************************************************************/
	json Game::LoadDictionary(std::string filename);

	/**************************************************************************************************/
	/**
	 * @fn	PyObject Game::*GetPyModule(const char *name);
	 *
	 * @brief	Gets python module.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param	name	The name.
	 *
	 * @return	Null if it fails, else the py module.
	 **************************************************************************************************/
	PyObject *GetPyModule(const char *name);

	/**************************************************************************************************/
	/**
	 * @fn	void Game::AddPyModule(const char *name, PyObject *module);
	 *
	 * @brief	Adds a py module to 'module'.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param 		  	name  	The name.
	 * @param [in,out]	module	If non-null, the module.
	 **************************************************************************************************/
	void AddPyModule(const char *name, PyObject *module);

	/**************************************************************************************************/
	/**
	 * @fn	glm::mat4 Game::GetViewMatrix();
	 *
	 * @brief	Gets view matrix.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @return	The view matrix.
	 **************************************************************************************************/
	glm::mat4 GetViewMatrix();

	/**************************************************************************************************/
	/**
	 * @fn	glm::mat4 Game::GetProjectionMatrix();
	 *
	 * @brief	Gets projection matrix.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @return	The projection matrix.
	 **************************************************************************************************/
	glm::mat4 GetProjectionMatrix();

};

extern Game *game;  /**< The game */