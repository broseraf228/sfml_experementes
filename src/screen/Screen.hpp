#ifndef BS_SCREEN_H
#define BS_SCREEN_H

#include "SFML/Graphics.hpp"


class Tile_atlas;

class Screen
{
private:
	static Screen* self;

	sf::RenderWindow window;
	~Screen();
	Screen(int size_x, int size_y);

	//current level map size
	int level_sx, level_sy;
	//current tile atlas 
	const Tile_atlas* level_tile_atlas;

	//level map vertex array
	sf::VertexArray displaying_map;
	//add block to displaying map
	void set_block_vertextes(int px, int py, const std::string& name);
	
public:
	Screen(const Screen&) = delete;
	
	static int Initialisation(int size_x, int size_y);

	static Screen* getInstance();
	static void close();

	void clear();
	void draw_level();
	void draw_fps(float fps);
	void display();
	//generate displaying_map and other variales from level
	void update_displaying_map(const Tile_atlas* tile_atlas, const std::vector<std::vector<std::string>>& map);

	sf::RenderWindow& get_window();
};

#endif