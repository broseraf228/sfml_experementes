
#include "SFML/Graphics.hpp"

#include "resource_manager/ResourceManager.hpp"
#include "screen/Screen.hpp"
#include "events/Events.hpp"
#include "game/Game.hpp"

#include <iostream>


double DELTA = 0.1;
float gTime = 0;

void close_all(){
    Screen::close();
    Game::close();
}

int main(int argc, char* argv[])
{
    std::string path = argv[0];
    while (path[path.size() - 1] != '\\')
        path.erase(path.size() - 1);
    ResourceManager::Initialisation(path);


    Screen::Initialisation(1600, 1200);
    Game::Initialisation();

    Screen* screen = Screen::getInstance();
    Game* game = Game::getInstance();

    sf::Clock clock;
    sf::Time time;
    while (Events::windowIsOpen())
    {
        Events::poolEvents();

        game->update();

        screen->clear();
        game->draw();
        screen->display();

        time = clock.restart();
        DELTA = time.asSeconds();
        gTime += DELTA;
    }

    close_all();

    return 0;
}