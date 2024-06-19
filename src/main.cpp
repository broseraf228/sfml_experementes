
#include "SFML/Graphics.hpp"

#include "screen/Screen.hpp"
#include "events/Events.hpp"

#include <iostream>

void close_all(){
    Screen::close();
}

int main()
{
    Screen::Initialisation(200, 200);

    Screen* screen = Screen::getInstance();

    sf::RenderWindow& window = screen->get_window();


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (Events::windowIsOpen())
    {
        Events::poolEvents();

        if (Events::justClicked(sf::Mouse::Button::Left))
            if(shape.getFillColor() == sf::Color::Green)
                shape.setFillColor(sf::Color::Red);
            else
                shape.setFillColor(sf::Color::Green);

        window.clear();
        window.draw(shape);
        window.display();
    }


    close_all();

    return 0;
}