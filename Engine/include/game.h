#pragma once

class Game
{
	sf::Clock _clock;
	sf::Window _window;
	bool _ended;
	sf::Time _lastUpdateTime;
	std::map<std::string, sf::Texture*> _textures;
public:
	sf::Time Time();
	Game();
	void Startup();
	void Input();
	void Update();
	void Draw();
	void Shutdown();
	sf::Texture *LoadTexture(std::string filename);
	bool Ended();
	sf::Time Delta();
};

extern Game *game;