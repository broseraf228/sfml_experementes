
#include "Game.hpp"
#include "../constants.hpp"

#include "SFML/Graphics.hpp"
#include "../screen/Screen.hpp"
#include "../screen/tile_atlas.hpp"
#include "../events/Events.hpp"
#include "../resource_manager/ResourceManager.hpp"
#include "world/World.hpp"
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
	//
	Screen::getInstance()->set_block_tile_atlas(ResourceManager::asset->get_tile_atlas("blocks_default"));
	//
	Screen::getInstance()->set_room_tile_atlas(ResourceManager::asset->get_tile_atlas("room_decorations_default"));

	world = new World();
	
	player_animation = new Animation(ResourceManager::asset->get_animation("player_animation"));
	subscribe_animation(player_animation);
	
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
		world->was_updated = false;
		screen->update_displaying(world->get_room());
	}

	screen->draw_room();
	screen->get_window().draw(player_sprite);
}


void Game::subscribe_animation(Animation* animation){
	animations.push_back(animation);
}
void Game::describe_animation(Animation* animation) {
	animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());
}
