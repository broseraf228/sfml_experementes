
#include "Events.hpp"

#include "SFML/Graphics.hpp"
#include "../screen/Screen.hpp"

#include <iostream>

extern void close_all();

//init variables
bool Events::m_windowIsOpen = true;
std::map<int, int> Events::keyboard_buttons{};
std::map<int, int> Events::mouse_buttons{};

void Events::poolEvents()
{
    sf::RenderWindow& window = Screen::getInstance()->get_window();

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed: // close the winsow
            m_windowIsOpen = false;
            break;

        case sf::Event::KeyPressed: // keyboard pressed
            if (keyboard_buttons.find(event.key.scancode) != keyboard_buttons.end())
                keyboard_buttons[event.key.scancode]++;
            else
                keyboard_buttons[event.key.scancode] = 1;
            break;

        case sf::Event::KeyReleased: // keyboard released
            keyboard_buttons[event.key.scancode] = 0;

            break;

        case sf::Event::MouseButtonPressed: // mouse pressed
               mouse_buttons[event.mouseButton.button] = 1;
            break;

        case sf::Event::MouseButtonReleased: // mouse released
            mouse_buttons[event.mouseButton.button] = 0;
            break;
        }
    }

    for (auto& item : mouse_buttons)
        if (item.second) {
            item.second++;
        }
}

bool Events::isPressed(int button) {
    if (keyboard_buttons.find(button) == keyboard_buttons.end())
        return false;
    return keyboard_buttons[button];
}
bool Events::justPressed(int button) {
    if (keyboard_buttons.find(button) == keyboard_buttons.end())
        return false;
    return keyboard_buttons[button] == 1;
}
bool Events::isClicked(int button) {
    if (mouse_buttons.find(button) == mouse_buttons.end())
        return false;
    return mouse_buttons[button];
}
bool Events::justClicked(int button) {
    if (mouse_buttons.find(button) == mouse_buttons.end())
        return false;
    return mouse_buttons[button] == 2;
}

bool Events::windowIsOpen() {
    return m_windowIsOpen;
}