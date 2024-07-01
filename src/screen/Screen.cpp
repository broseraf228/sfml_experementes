
#include "Screen.hpp"

#include "../game/Game.hpp"
#include "../game/world/Room.hpp"
#include "../game/world/Block.hpp"
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
void Screen::set_camera_position(int px, int py) {
	camera_position_x = px, camera_position_y = py;
}
void Screen::set_block_tile_atlas(const Tile_atlas* atlas) {
	block_tile_atlas = atlas;
}
void Screen::set_room_tile_atlas(const Tile_atlas* atlas){
	room_tile_atlas = atlas;
}

void Screen::set_block_vertextes(int px, int py, const std::string& name, const Tile_atlas* atlas, sf::VertexArray& vertarray) {
	//tile intrect on atlas
	const texRect& rectangle = atlas->get_tile_fragment(name);
	//x size of tile texture
	int Tsx = rectangle.width;
	//y size of tile texture
	int Tsy = rectangle.height;
	//x position of tile texture on tile atlas
	int Tpx = rectangle.px;
	//x position of tile texture on tile atlas
	int Tpy = rectangle.py;

	//size of one tile on map
	int size = atlas->get_tile_size();

	//x position on screen
	int left = px * size;
	//y position on screen
	int top = py * size;

	float r1 = ((float)window.getSize().y / float(size * (12 + 1)));
	int dx = (window.getSize().x - level_sx * size * r1) / 2 + camera_position_x;
	int dy = (window.getSize().y - level_sy * size * r1) / 2 + camera_position_y;

	int corr_y = rectangle.dy;

	int vertex_number = (py * level_sx + px) * 4;
	vertarray.append(sf::Vertex(
		sf::Vector2f
		(
			floor(left * r1 + dx),
			floor((top + corr_y) * r1 + dy)
		),
		sf::Vector2f(
			(Tpx),
			(Tpy)
		)));
	vertarray.append(sf::Vertex(
		sf::Vector2f
		(
			floor((left + Tsx) * r1 + dx),
			floor((top + corr_y) * r1 + dy)
		),
		sf::Vector2f(
			(Tpx + Tsx),
			(Tpy)
		)));
	vertarray.append(sf::Vertex(
		sf::Vector2f(
			floor((left + Tsx) * r1 + dx),
			floor((top + Tsy + corr_y) * r1 + dy)
		),
		sf::Vector2f(
			(Tpx + Tsx),
			(Tpy + Tsy)
		)));
	vertarray.append(sf::Vertex(
		sf::Vector2f(
			floor(left * r1 + dx),
			floor((top + Tsy + corr_y) * r1 + dy)
		),
		sf::Vector2f(
			(Tpx),
			(Tpy + Tsy)
		)));
}

void Screen::update_displaying(const Room* room){
	level_sx = room->get_map().get_map().size();
	level_sy = room->get_map().get_map()[0].size();

	const std::vector<std::vector<Block*>>& map = room->get_map().get_map();

	displaying_blocks.clear();
	displaying_blocks.resize(level_sx * level_sy * 4);
	for (int y = 0; y < level_sy; y++)
		for (int x = 0; x < level_sx; x++)
			set_block_vertextes(x, y, map[x][y]->get_texture_name(), block_tile_atlas, displaying_blocks);

	displaying_room_decorations.clear();
	displaying_room_decorations.resize(((level_sx + level_sy) * 2 + 4) * 4 + level_sx * level_sy * 4);
	for (int y = 0; y < level_sy; y++)
		for (int x = 0; x < level_sx; x++)
			set_block_vertextes(x, y, "m", room_tile_atlas, displaying_room_decorations);
	for (int x = 0; x < level_sx; x++)
		set_block_vertextes(x, -1, "t", room_tile_atlas, displaying_room_decorations);
	for (int x = 0; x < level_sx; x++)
		set_block_vertextes(x, level_sy, "b", room_tile_atlas, displaying_room_decorations);
	for (int y = 0; y < level_sy; y++)
		set_block_vertextes(-1, y, "l", room_tile_atlas, displaying_room_decorations);
	for (int y = 0; y < level_sy; y++)
		set_block_vertextes(level_sx, y, "r", room_tile_atlas, displaying_room_decorations);
	set_block_vertextes(-1, -1, "lt", room_tile_atlas, displaying_room_decorations);
	set_block_vertextes(level_sx, -1, "rt", room_tile_atlas, displaying_room_decorations);
	set_block_vertextes(level_sx, level_sy, "rb", room_tile_atlas, displaying_room_decorations);
	set_block_vertextes(-1, level_sy, "lb", room_tile_atlas, displaying_room_decorations);
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

	displaying_blocks.setPrimitiveType(sf::Quads);
	displaying_room_decorations.setPrimitiveType(sf::Quads);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(
		sf::VideoMode(size_x, size_y), 
		"SFML works!",
		sf::Style::Close,
		settings);
}


void Screen::draw_room(){
	window.draw(displaying_room_decorations, room_tile_atlas->get_texture());
	window.draw(displaying_blocks, block_tile_atlas->get_texture());
}
void draw_fps(float fps) {

}

void Screen::clear() {
	window.clear();
}

void Screen::display() {
	window.display();
}
