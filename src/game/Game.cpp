
#include "Game.hpp"
#include "../constants.hpp"

#include "SFML/Graphics.hpp"
#include "../screen/Screen.hpp"
#include "../screen/tile_atlas.hpp"
#include "../events/Events.hpp"
#include "../resource_manager/ResourceManager.hpp"
#include "World.hpp"
#include <iostream>

extern double DELTA;

Game* Game::self = nullptr;

int Game::Initialisation() {
	if (self != nullptr)
		return 1;
	self = new Game();
	return 0;
}
void Game::close() {
	if (self == nullptr)
		return;

	delete self;
	self = nullptr;
}
Game* Game::getInstance() {
	if (self == nullptr)
		std::cout << "game called befote initialisation" << std::endl;
	return self;
}

Game::~Game() {}
Game::Game() {

	ResourceManager::load_image("img\\blocks\\level_1.png", "i_level_1");
	ResourceManager::load_texture(ResourceManager::get_image("i_level_1"), sf::IntRect(0,0,128,128), "te_level_1");

	ResourceManager::load_image("img\\animations\\player_animations.png", "i_player_animations");
	ResourceManager::load_texture(ResourceManager::get_image("i_player_animations"), sf::IntRect(0,0,128,128), "te_player_animations");

	world = new World();
	int ds = 24;
	atlas = new Tile_atlas(ResourceManager::get_texture("te_level_1"), ds,
		{ 
			{"air" , sf::IntRect(		0,		ds,		ds,-ds)},
			{"rock" , sf::IntRect(		ds*1,	ds,		ds,-ds)},
			{"stone" , sf::IntRect(		ds*2,	ds,		ds,-ds)},
		}
	);

	player_animation = new Animation(ResourceManager::get_texture("te_player_animations"),16,16,2);
	subscribe_animation(player_animation);
	
	player_sprite.setTextureRect(sf::IntRect(0,0,16,16));
	player_sprite.setOrigin(8, 8);
	player_sprite.setScale(10, 10);
}

void Game::update()
{
	//update_animations
	for (auto item : animations)
		item->update_time(DELTA);

	if (Events::isPressed(sf::Keyboard::W))
		player_sprite.move(0,-100 * DELTA);
	if (Events::isPressed(sf::Keyboard::S))
		player_sprite.move(0, 100 * DELTA);
	if (Events::isPressed(sf::Keyboard::D))
		player_sprite.move(100 * DELTA, 0);
	if (Events::isPressed(sf::Keyboard::A))
		player_sprite.move(-100 * DELTA, 0);

	player_animation->update_sprite(player_sprite);
}

void Game::draw()
{
	Screen* screen = Screen::getInstance();

	if (world->was_updated) {
		//world->was_updated = false;
		screen->update_displaying_map(atlas, world->get_level_map_textures());
	}

	screen->draw_level();
	screen->get_window().draw(player_sprite);
}


void Game::subscribe_animation(Animation* animation){
	animations.push_back(animation);
}
void Game::describe_animation(Animation* animation) {
	animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());
}
