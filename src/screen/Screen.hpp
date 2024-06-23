#ifndef BS_SCREEN_H
#define BS_SCREEN_H

#include "SFML/Graphics.hpp"


struct gameDrawableData;


class Screen
{
private:
	static Screen* self;

	sf::RenderWindow window;
	~Screen();
	Screen(int size_x, int size_y);
public:
	Screen(const Screen&) = delete;
	
	static int Initialisation(int size_x, int size_y);

	static Screen* getInstance();
	static void close();

	void clear();

	void display();

	sf::RenderWindow& get_window();
};

#endif