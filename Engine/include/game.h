#pragma once

class Game
{
	sf::Clock m_clock;
	sf::Window m_window;
	bool m_ended;
	sf::Time m_lastUpdateTime;
	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, Shader*> m_shaders;
	glm::vec2 m_screen;
public:
	sf::Time Time();
	Game();
	void Startup();
	void Input();
	void Update();
	void Draw();
	void Shutdown();
	sf::Texture *LoadTexture(std::string filename);
	sf::Shader *LoadShader(std::string name, ::string vert_file, std::string frag_file);
	sf::Shader *Shader(std::string name);
	bool Ended();
	sf::Time Delta();
	glm::vec2 Screen();
};

extern Game *game;