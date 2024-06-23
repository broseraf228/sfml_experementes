#ifndef BS_GAME_H
#define BS_GAME_H

#include "SFML/Graphics.hpp"

class Game {
private:
	static Game* self;

	Game();
	~Game();

	//game content
	int current_state{ 0 };
	sf::Sprite player_sprite;

public:

	static int Initialisation();

	static Game* getInstance();
	static void close();

	void update();

	void draw();
};

#endif