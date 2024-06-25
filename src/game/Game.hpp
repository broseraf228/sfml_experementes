#ifndef BS_GAME_H
#define BS_GAME_H

#include "SFML/Graphics.hpp"
#include <map>

class World;
class Tile_atlas;
enum class BLOCKS;

class Game {
private:
	static Game* self;

	Game();
	~Game();

	//game content
	World* world;

	int current_state{ 0 };
	sf::Sprite player_sprite;

	Tile_atlas* atlas;

public:

	static int Initialisation();

	static Game* getInstance();
	static void close();

	void update();

	void draw();
};

#endif