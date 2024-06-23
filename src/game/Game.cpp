
#include "Game.hpp"

#include "SFML/Graphics.hpp"
#include "../screen/Screen.hpp"
#include "../events/Events.hpp"
#include "../resource_manager/ResourceManager.hpp"
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
	sf::RenderWindow& window = Screen::getInstance()->get_window();

	window.draw(player_sprite);
}
