#ifndef BS_SCREEN_H
#define BS_SCREEN_H

#include "SFML/Graphics.hpp"


class Tile_atlas;
class Room;

class Screen
{
private:
	static Screen* self;

	sf::RenderWindow window;
	~Screen();
	Screen(int size_x, int size_y);

	//current level map size
	int level_sx, level_sy;
	//current block tile atlas 
	const Tile_atlas* block_tile_atlas;
	//current room tile atlas 
	const Tile_atlas* room_tile_atlas;

	//level map vertex array
	sf::VertexArray displaying_blocks;
	//floor and barriers vertex array
	sf::VertexArray displaying_room_decorations;
	//add block to displaying map
	void set_block_vertextes(int px, int py, const std::string& name, const Tile_atlas* atlas, sf::VertexArray& vertarray);
	//camera position
	int camera_position_x{ 0 }, camera_position_y{ 0 };
	
public:
	Screen(const Screen&) = delete;
	
	static int Initialisation(int size_x, int size_y);

	static Screen* getInstance();
	static void close();

	void clear();
	void draw_room();
	void draw_fps(float fps);
	void display();

	//generate displaying_map and other variales from level
	void update_displaying(const Room* room);

	void set_block_tile_atlas(const Tile_atlas*);
	void set_room_tile_atlas(const Tile_atlas*);
	void set_camera_position(int px, int py);
	sf::RenderWindow& get_window();
};

#endif