
#include "Screen.hpp"

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

Screen::~Screen() {
	window.close();
}
Screen::Screen(int size_x, int size_y) {
	if (self != nullptr) {
		std::cout << "screen double initialisation" << std::endl;
		return;
	}
	self = this;

	window.create(sf::VideoMode(size_x, size_y), "SFML works!");
}

sf::RenderWindow& Screen::get_window() {
	return window;
}

