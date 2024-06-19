#ifndef BS_EVENTS_H
#define BS_EVENTS_H

#include <string>
#include <map>

class Events
{
public:
	static void poolEvents();

	static bool isPressed(int);
	static bool justPressed(int);

	static bool isClicked(int);
	static bool justClicked(int);

	static bool windowIsOpen();
private:

	static bool m_windowIsOpen;

	static std::map<int, int> keyboard_buttons;
	static std::map<int, int> mouse_buttons;
};
#endif