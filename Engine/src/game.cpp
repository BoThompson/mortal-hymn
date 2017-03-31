/**************************************************************************************************/
/**
 * @file src\game.cpp
 *
 * Implements the game class.
 ***************************************************************************************************/
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.h"
#include "entity.h"
#include "game.h"
/**************************************************************************************************/
#define SCREEN_WIDTH 1600.0f
#define SCREEN_HEIGHT 1200.0f


/**************************************************************************************************
 * TEST CODE
/**************************************************************************************************/
static const std::vector<glm::vec2> UVs = {
	{ 0, 0 },
	{ 1, 1 },
	{ 0, 1 },

	{ 0, 0 },
	{ 1, 0 },
	{ 1, 1 }
};

static const std::vector<glm::vec3> points = {
	//Upper Left Triangle
	{ -1, -1, -10 },
	{ 1, 1, -10 },
	{ -1, 1, -10 },
	//Lower Right Triangle
	{ -1, -1, -10 },
	{ 1, -1, -10 },
	{ 1, 1, -10 }


	//Colors!
	//{1, .5, 1},
	//{.5, 1, 0},
	//{0, .5, 1},

	//Barycentric!
	//{1, 0, 0 },
	//{0, 1, 0 },
	//{0, 0, 1 }
}
;
/**************************************************************************************************/
sf::Time Game::Time()
{
	return m_clock.getElapsedTime();
}
/**************************************************************************************************/
Game::Game()
{

}
/**************************************************************************************************/
void Game::Startup()
{

	int err;
	m_contextSettings.depthBits = 24;
	m_contextSettings.stencilBits = 8;
	m_contextSettings.antialiasingLevel = 4;
	m_contextSettings.majorVersion = 4;
	m_contextSettings.minorVersion = 3;
	m_window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Mortal Hymn", sf::Style::Default, m_contextSettings);
	m_entities.resize(STARTING_MAX_ENTITIES);
	memset(&m_entities[0], 0, sizeof(Entity) * STARTING_MAX_ENTITIES);
	if ((err = glewInit()) != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
		return;
	}


	//m_modelMatrix = glm::mat4(1.0);
	m_viewMatrix = glm::mat4(1.0);
	m_cameraPosition = glm::vec3(0, 0, 1);
	m_cameraRotation = glm::vec3(0, 0, 0);
	m_projectionMatrix = glm::perspective(glm::radians(35.0f), 
							SCREEN_HEIGHT / SCREEN_WIDTH, 1.0f, 100.0f);
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_UVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	Entity *e = NewEntity();
	e->SetVertices(points);
	std::vector<glm::vec3> v = e->Vertices();
	glBufferData(GL_ARRAY_BUFFER, e->Vertices().size() * sizeof(glm::vec3), &e->Vertices()[0][0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVbo);
	e->SetUVs(UVs);
	glBufferData(GL_ARRAY_BUFFER, e->UVs().size() * sizeof(glm::vec2), &e->UVs()[0][0], GL_STATIC_DRAW);
	m_lastUpdateTime = m_clock.getElapsedTime();
	sf::Texture texPic;
	sf::Image imagePic;
	imagePic.loadFromFile("images\\test.png");
	imagePic.flipVertically();
	texPic.loadFromImage(imagePic);
	setup_python();
	Actor *test_machine = new Actor(e, "testFSM");
	m_currentShader = LoadShader("Default", "uv.vert", "uv.frag");
	json dict = LoadDictionary("data/test.def");
	printf("%s\n", dict.dump().c_str());
	return;
}
/**************************************************************************************************/
void Game::Input()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::KeyPressed)
			switch (event.key.code)
			{
			case sf::Keyboard::Right:
				game->TranslateCamera(glm::vec3(.01f, 0, 0));
				break;
			case sf::Keyboard::Left:
				game->TranslateCamera(glm::vec3(-.01f, 0, 0));
				break;
			case sf::Keyboard::Up:
				game->TranslateCamera(glm::vec3(0, .01f, 0));
				break;
			case sf::Keyboard::Down:
				game->TranslateCamera(glm::vec3(0, -.01f, 0));
				break;
			case sf::Keyboard::A:
				game->RotateCamera(glm::vec3(0, 0, .01f));
				break;
			case sf::Keyboard::D:
				game->RotateCamera(glm::vec3(0, 0, -.01f));
				break;
			case sf::Keyboard::W:
				game->RotateCamera(glm::vec3(0, .01f, 0));
				break;
			case sf::Keyboard::S:
				game->RotateCamera(glm::vec3(0, -.01f, 0));
				break;
			}
	}
}
/**************************************************************************************************/
void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_viewMatrix = glm::lookAt(glm::vec3(m_cameraPosition), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	m_MVP = m_projectionMatrix * m_viewMatrix;
	for (std::vector<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		if(it->InUse())
			it->Draw(*m_currentShader, m_MVP);
	m_window.display();
}
/**************************************************************************************************/
void Game::Update()
{
	for (std::vector<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		it->Update();
	m_lastUpdateTime = m_clock.getElapsedTime();
}
/**************************************************************************************************/
void Game::Shutdown()
{

}
/**************************************************************************************************/
bool Game::Ended()
{
	return m_ended;
}
/**************************************************************************************************/
sf::Time Game::Delta()
{
	return  m_clock.getElapsedTime() - m_lastUpdateTime;
}
/**************************************************************************************************/
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
/**************************************************************************************************/
glm::vec2 Game::Screen()
{
	return m_screen;
}
/**************************************************************************************************/
Shader *Game::LoadShader(std::string name,
	std::string vert_file, std::string frag_file)
{
	Shader *shader = new Shader(name, vert_file, frag_file);
	if (shader->IsValid())
	{
		m_shaders[name] = shader;
		return shader;
	}else{
		printf("Error: Game::LoadShader failed to load a valid shader.\n");
		return NULL;
	}
}
/**************************************************************************************************/
json Game::LoadDictionary(std::string filename)
{
	static std::vector<char> dict_string;
	json dict;
	FILE *fp;
	fp = fopen(filename.c_str(), "r");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (dict_string.size() < size)
		dict_string.resize(size+1);
	fread(&dict_string[0], size, 1, fp);
	fclose(fp);
	dict_string[size] = '\0';
    return json::parse(&dict_string[0]);
}
/**************************************************************************************************/
Shader *Game::GetShader(std::string name)
{
	std::map<std::string, Shader*>::iterator it;
	if ((it = m_shaders.find(name)) != m_shaders.end())
	{
		return (it->second);
	}
	else
		return NULL;
}
/**************************************************************************************************/
void Game::UseShader(std::string name)
{
	Shader *s = NULL;
	std::map<std::string, Shader*>::iterator it;
	if ((it = m_shaders.find(name)) != m_shaders.end())
	{
		s = (it->second);
	}
	if (s)
		s->Use();
}
/**************************************************************************************************/
void Game::TranslateCamera(glm::vec3 vector)
{
	m_cameraPosition += vector;
}
/**************************************************************************************************/
void Game::RotateCamera(glm::vec3 vector)
{
	m_cameraRotation += vector;
}
/**************************************************************************************************/
void Game::SetCameraRotation(glm::vec3 vector)
{
	m_cameraRotation = vector;
}
/**************************************************************************************************/
Entity *Game::NewEntity()
{
	int oldsize;
	for (std::vector<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		if (!it->InUse())
		{
			it->Initialize();
			return it._Ptr;
		}
	//Run out of room, allocate more
	oldsize = m_entities.size();
	m_entities.resize(m_entities.size() * 2);
	memset(&m_entities[oldsize], 0, sizeof(Entity) * (m_entities.size() - oldsize));
	Entity *e = &m_entities[oldsize];
	e->Initialize();
	return e;
}
/**************************************************************************************************/
GLuint Game::Vbo()
{
	return m_vbo;
}
/**************************************************************************************************/
GLuint Game::UVbo()
 {
	 return m_UVbo;
 }
/**************************************************************************************************/
