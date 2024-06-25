
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

	ResourceManager::load_image("textures\\blocks\\level_1.png", "i_level_1");
	ResourceManager::load_texture(ResourceManager::get_image("i_level_1"), sf::IntRect(0,0,128,128), "ta_level_1");

	world = new World();
	atlas = new Tile_atlas(ResourceManager::get_texture("ta_level_1"), 16,
		{ 
			{int(bsc::BLOCKS::Air) , Tile_atlas_fragment(0,0,1,1)},
			{int(bsc::BLOCKS::Rock) , Tile_atlas_fragment(1,0,2,1)},
		}
	);
	
	player_sprite.setTextureRect(sf::IntRect(0,0,16,16));
	player_sprite.setOrigin(8, 8);
	player_sprite.setScale(10, 10);
}

void Game::update()
{
	if (Events::justClicked(sf::Mouse::Button::Left))
		if (current_state == 1)
			current_state = 0;
		else
			current_state = 1;

	if (Events::isPressed(sf::Keyboard::W))
		player_sprite.move(0,-100 * DELTA);
	if (Events::isPressed(sf::Keyboard::S))
		player_sprite.move(0, 100 * DELTA);

	if (current_state == 0)
		player_sprite.setTexture(*ResourceManager::get_texture("playerState_1"));
	if (current_state == 1)
		player_sprite.setTexture(*ResourceManager::get_texture("playerState_2"));
}

void Game::draw()
{
	Screen* screen = Screen::getInstance();

	if (world->was_updated) {
		world->was_updated = false;
		screen->update_displaying_map(atlas, world->get_level_map_textures());
	}

	screen->draw_level();
	screen->get_window().draw(player_sprite);
}
