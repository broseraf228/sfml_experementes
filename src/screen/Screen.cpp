
#include "Screen.hpp"

#include "../game/Game.hpp"
#include "../resource_manager/ResourceManager.hpp"
#include "tile_atlas.hpp"
#include "../constants.hpp"
#include <iostream>

extern float gTime;

inline int inmap(int p, int s) {
	if (p < 0) return 0;
	if (p > s) return s;
	return p;
}

Screen* Screen::self = nullptr;
int Screen::Initialisation(int size_x, int size_y) {
	if (self != nullptr)
		return 1;
	self = new Screen(size_x, size_y);
}
void Screen::close() {
	if (self == nullptr)
		return;

	delete self;
	self = nullptr;
}
Screen* Screen::getInstance() {
	if (self == nullptr)
		std::cout << "screen called befote initialisation" << std::endl;
	return self;
}

sf::RenderWindow& Screen::get_window() {
	return window;
}

void Screen::set_block_vertextes(int px, int py, const std::string& name) {
	//tile intrect on atlas
	const sf::IntRect& rectangle = level_tile_atlas->get_tile_fragment(name);
	//x size of tile texture
	int Tsx = rectangle.width;
	//y size of tile texture
	int Tsy = rectangle.height;
	//x position of tile texture on tile atlas
	int Tpx = rectangle.left;
	//x position of tile texture on tile atlas
	int Tpy = rectangle.top;

	//size of one tile on map
	int size = level_tile_atlas->get_tile_size();

	//x position on screen
	int left = px * size;
	//y position on screen
	int top = py * size;

	float r1 = (float)window.getSize().y / float(size * (12));
	int dx = (window.getSize().x - level_sx * size * r1) / 2;

	int vertex_number = (py * level_sx + px) * 4;
	displaying_map[vertex_number] = sf::Vertex(
		sf::Vector2f
		(
			floor(left * r1 + dx),
			floor((top - Tsy) * r1)
		), 
		sf::Vector2f(
			(Tpx),
			(Tpy)
		));
	displaying_map[vertex_number+1] = sf::Vertex(
		sf::Vector2f
		(
			floor((left + Tsx) * r1 + dx),
			floor((top - Tsy) * r1)
		), 
		sf::Vector2f(
			(Tpx + Tsx),
			(Tpy)
		));
	displaying_map[vertex_number+2] = sf::Vertex(
		sf::Vector2f(
			floor((left + Tsx) * r1 + dx),
			floor((top) * r1)
		), 
		sf::Vector2f(
			(Tpx + Tsx),
			(Tpy + Tsy)
		));
	displaying_map[vertex_number+3] = sf::Vertex(
		sf::Vector2f(
			floor(left * r1 + dx),
			floor((top) * r1)
		), 
		sf::Vector2f(
			(Tpx),
			(Tpy + Tsy)
		));
}
void Screen::update_displaying_map(const Tile_atlas* tile_atlas, const std::vector<std::vector<std::string>>& map){
	level_tile_atlas = tile_atlas;
	level_sx = map.size();
	level_sy = map[0].size();

	displaying_map.resize(level_sx * level_sy * 4);

	for (int y = 0; y < level_sy; y++)
		for (int x = 0; x < level_sx; x++)
			set_block_vertextes(x, y, map[x][y]);
}

Screen::~Screen() {
	window.close();
}
Screen::Screen(int size_x, int size_y) {
	if (self != nullptr) {
		std::cout << "screen double initialisation" << std::endl;
		return;
	}
	self = this;

	displaying_map.setPrimitiveType(sf::Quads);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(
		sf::VideoMode(size_x, size_y), 
		"SFML works!",
		sf::Style::Close,
		settings);
}


void Screen::draw_level(){
	window.draw(displaying_map, level_tile_atlas->get_texture());
}
void draw_fps(float fps) {

}

void Screen::clear() {
	window.clear();
}

void Screen::display() {
	window.display();
}
