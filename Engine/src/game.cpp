/**************************************************************************************************/
/**
 * @file src\game.cpp
 *
 * Implements the game class.
 ***************************************************************************************************/
#include "game.h"
/**************************************************************************************************/
#define SCREEN_WIDTH 1600.0f
#define SCREEN_HEIGHT 1200.0f

/**************************************************************************************************
 * TEST CODE
/**************************************************************************************************/

glm::vec3 lightSource[5];
GLfloat lightPower[5];
glm::vec3 lightColor[5];

/**************************************************************************************************/
sf::Time Game::Time()
{
	return m_clock.getElapsedTime();
}
/**************************************************************************************************/
Game::Game()
{

}
Entity *e;// = NewEntity();

/**************************************************************************************************/
void Game::Startup()
{
	int err;
	m_process = false;
	m_screen = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_contextSettings.depthBits = 24;
	m_contextSettings.stencilBits = 8;
	m_contextSettings.antialiasingLevel = 4;
	m_contextSettings.majorVersion = 4;
	m_contextSettings.minorVersion = 3;
	m_window.create(sf::VideoMode((unsigned int)SCREEN_WIDTH, (unsigned int)SCREEN_HEIGHT), "Mortal Hymn", sf::Style::Default, m_contextSettings);
	m_entities.resize(STARTING_MAX_ENTITIES);
	memset(&m_entities[0], 0, sizeof(Entity) * STARTING_MAX_ENTITIES);
	if ((err = glewInit()) != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
		return;
	}


	//m_modelMatrix = glm::mat4(1.0);
	m_viewMatrix = glm::mat4(1.0);
	m_cameraPosition = glm::vec3(0, 0, 5);
	m_cameraRotation = glm::vec3(0, 0, 0);
	m_projectionMatrix = glm::perspective(glm::radians(35.0f), 
							SCREEN_WIDTH / (SCREEN_HEIGHT + 200), 1.0f, 10.0f);
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_UVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);	
	m_lastUpdateTime = m_clock.getElapsedTime();
	setup_python();
	m_currentShader = LoadShader("Default", "uv.vert", "uv.frag");
	m_currentShader = LoadShader("Lit", "lit.vert", "lit.frag");
	lightPower[0] = 20;
	lightSource[0] = glm::vec3(5, 1, 10);
	lightColor[0] = glm::vec3(1, 0, 0);
	lightPower[1] = 50;
	lightSource[1] = glm::vec3(-3, -3, 10);
	lightColor[1] = glm::vec3(0, 1, 1);
	glUseProgram(m_currentShader->GetProgramID());
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glUniform3fv(m_currentShader->Uniform("LightPosition_worldspace"), 5, &lightSource[0][0]);
	glUniform1fv(m_currentShader->Uniform("LightPower"), 5, &lightPower[0]);
	glUniform3fv(m_currentShader->Uniform("LightColor"), 5, &lightColor[0][0]);
	json dict = LoadDictionary("data/test.def");
	e = NewEntity();
	e->LoadFromDict(dict);
	e->Translate(glm::vec3(0, 0, -5));
//	e->SetRotation(glm::vec3(90, 0, 30));
	m_player = e;
	Shader *testShader = LoadShader("Postprocess", "postprocess.vert", "postprocess.frag");
	printf("%s\n", dict.dump().c_str());
	m_testProcess = new PostProcess(testShader);
	m_testProcess2 = new PostProcess(testShader);

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
				TranslateCamera(glm::vec3(-.05f, 0, 0));
				break;
			case sf::Keyboard::Left:
				TranslateCamera(glm::vec3(.05f, 0, 0));
				break;
			case sf::Keyboard::Up:
				TranslateCamera(glm::vec3(0, -.05f, 0));
				break;
			case sf::Keyboard::Down:
				TranslateCamera(glm::vec3(0, .05f, 0));
				break;
			case sf::Keyboard::LBracket:
				m_player->SetRotation(m_player->Rotation() + glm::vec3(0, .05f, 0));
				break;
			case sf::Keyboard::RBracket:
				m_player->SetRotation(m_player->Rotation() - glm::vec3(0, .05f, 0));
				break;
			case sf::Keyboard::A:
				RotateCamera(glm::vec3(0, 0, .01f));
				break;
			case sf::Keyboard::D:
				RotateCamera(glm::vec3(0, 0, -.01f));
				break;
			case sf::Keyboard::W:
				RotateCamera(glm::vec3(0, .01f, 0));
				break;
			case sf::Keyboard::S:
				RotateCamera(glm::vec3(0, -.01f, 0));
				break;
			case sf::Keyboard::Tab:
				m_process = (m_process+1)%3;
				break;
			}
	}
}
/**************************************************************************************************/
void Game::Draw()
{
	m_viewMatrix = glm::inverse(glm::translate(glm::mat4(1), m_cameraPosition) * glm::eulerAngleXYZ(m_cameraRotation.x, m_cameraRotation.y, m_cameraRotation.z));
	m_MVP = m_projectionMatrix * m_viewMatrix;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_process)
	{
		m_testProcess->Enable();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		for (std::vector<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
			if (it->InUse())
				it->Draw(*m_currentShader, m_MVP);
		Shader *processShader = m_testProcess->GetShader();
		Shader *prevShader = m_currentShader;
		m_currentShader = processShader;
		processShader->Use();
		glUniform1i(processShader->Uniform("ScreenWidth"), SCREEN_WIDTH);
		glUniform1i(processShader->Uniform("ScreenHeight"), SCREEN_HEIGHT);
		glm::mat3 m = glm::mat3(-1, -1, 0,
								-1, 0, 1,
								0, 1, 1);
		glUniformMatrix3fv(processShader->Uniform("kernel"), 1, GL_FALSE, &m[0][0]);
		m_testProcess->Disable();
		if (m_process == 2)	
		{
			m_testProcess2->Enable();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			m_testProcess->RenderQuad();
			m_testProcess2->Disable();
			m = (1.0f / 16) * glm::mat3(1, 2, 1,
				2, 4, 2,
				1, 2, 1);
			glUniformMatrix3fv(processShader->Uniform("kernel"), 1, GL_FALSE, &m[0][0]);

			m_testProcess2->RenderQuad();
		}
		else {
			m_testProcess->RenderQuad();
		}
		m_currentShader = prevShader;
		m_currentShader->Use();
	}
	else {
		for (std::vector<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
			if (it->InUse())
				it->Draw(*m_currentShader, m_MVP);
	}
	m_window.display();
}
/**************************************************************************************************/
/*
//Glow
GLuint fbo;
glGenFramebuffers(1, &fbo);
glBindFramebuffer(GL_FRAMEBUFFER, fbo);

GLuint textures[3];
glGenTextures(2, textures);
glBindTexture(GL_TEXTURE_2D, textures[0]);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH,SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[0], 0);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, HEIGHT, 0,
//		GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
GLuint rbo;
glGenRenderbuffers(1, &rbo);
glBindRenderbuffer(GL_RENDERBUFFER, rbo);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
for (std::vector<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
if (it->InUse())
it->Draw(*m_currentShader, m_MVP);
glBindFramebuffer(GL_FRAMEBUFFER, 0);
*/
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
Model *Game::LoadModel(std::string filename)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate);
	if (scene == NULL)
	{
		printf("Failure to load scene from %s.\n", filename.c_str());
	}
	Model *model;

	if (m_models.find(filename) != m_models.end())
	{
		return m_models[filename];
	}
	else
	{
		model = new Model();
		model->Load(scene);
		m_models[filename] = model;
		return model;
	}

}

/**************************************************************************************************/
Texture *Game::LoadTexture(std::string filename)
{
	Texture *tex;
	if (m_textures.find(filename) != m_textures.end())
	{
		return m_textures[filename];
	}
	else
	{
		tex = new Texture();
		tex->Load(filename);
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
	unsigned long size = ftell(fp);
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
Actor *Game::NewActor()
{
	int oldsize;
	for (std::vector<Actor>::iterator it = m_actors.begin(); it != m_actors.end(); it++)
		if (!it->InUse())
		{
			it->Reset();
			return it._Ptr;
		}
	//Run out of room, allocate more
	oldsize = m_actors.size();
	m_actors.resize(m_actors.size() * 2);
	memset(&m_actors[oldsize], 0, sizeof(Entity) * (m_actors.size() - oldsize));
	Actor *a = &m_actors[oldsize];
	a->Reset();
	return a;
}
/**************************************************************************************************/
PyObject *Game::GetPyModule(const char *name)
{
	if (m_pyModules.find(name) == m_pyModules.end())
		return NULL;
	else
		return m_pyModules[name];
}
/**************************************************************************************************/
void Game::AddPyModule(const char *name, PyObject *module)
{
	m_pyModules[name] = module;
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
glm::mat4 Game::GetViewMatrix()
{
	return m_viewMatrix;
}
/**************************************************************************************************/
glm::mat4 Game::GetProjectionMatrix()
{
	return m_projectionMatrix;
}
/**************************************************************************************************/
Shader *Game::GetCurrentShader()
{
	return m_currentShader;
}
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/