#ifndef BS_GAME_H
#define BS_GAME_H

#include "SFML/Graphics.hpp"
#include <map>

class World;
class Tile_atlas;
class Animation;
enum class BLOCKS;

class Game {
private:
	static Game* self;

	Game();
	~Game();

	//animations
	std::vector<Animation*> animations;

	//game content
	World* world;

	Animation* player_animation;
	sf::Sprite player_sprite;

	Tile_atlas* atlas;

public:

	static int Initialisation();

	static Game* getInstance();
	static void close();

	void update();
	void draw();

	void subscribe_animation(Animation*);
	void describe_animation(Animation*);
};

#endif