
#include "Screen.hpp"

#include "../game/Game.hpp"
#include "../resource_manager/ResourceManager.hpp"
#include "tile_atlas.hpp"
#include <iostream>



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

void Screen::set_block_vertextes(int px, int py, int name) {
	int size = level_tile_atlas->get_tile_size();
	int tpx = level_tile_atlas->get_tile_fragment(name).px, tpy = level_tile_atlas->get_tile_fragment(name).py;
	int tsx = level_tile_atlas->get_tile_fragment(name).sx, tsy = level_tile_atlas->get_tile_fragment(name).sy;

	int left = px * size, top = py * size; 

	float r1 = (float)window.getSize().y / float(size * (level_sy));
	int dx = (window.getSize().x - level_sx * size * r1) / 2;

	int vertex_number = (py * level_sx + px) * 4;
	displaying_map[vertex_number] = sf::Vertex(
		sf::Vector2f
		(
			floor(left * r1 + dx),
			floor(top * r1)
		), 
		sf::Vector2f(
			(tpx + px % tsx) * size,
			(tpy + py % tsy) * size
		));
	displaying_map[vertex_number+1] = sf::Vertex(
		sf::Vector2f
		(
			floor((left + size) * r1 + dx),
			floor(top * r1)
		), 
		sf::Vector2f(
			(tpx + 1 + px % tsx) * size,
			(tpy + py % tsy) * size
		));
	displaying_map[vertex_number+2] = sf::Vertex(
		sf::Vector2f(
			floor((left + size) * r1 + dx),
			floor((top + size) * r1)
		), 
		sf::Vector2f(
			(tpx + 1 + px % tsx) * size,
			(tpy + 1 + py % tsy) * size
		));
	displaying_map[vertex_number+3] = sf::Vertex(
		sf::Vector2f(
			floor(left * r1 + dx),
			floor((top + size) * r1)
		), 
		sf::Vector2f(
			(tpx + px % tsx) * size,
			(tpy + 1 + py % tsy) * size
		));
}
void Screen::update_displaying_map(const Tile_atlas* tile_atlas, std::vector<std::vector<int>> map){
	level_tile_atlas = tile_atlas;
	level_sx = map.size();
	level_sy = map[0].size();

	displaying_map.resize(level_sx * level_sy * 4);

	for (int y = 0; y < map.size(); y++)
		for (int x = 0; x < map[y].size(); x++)
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
	settings.antialiasingLevel = 16;
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
