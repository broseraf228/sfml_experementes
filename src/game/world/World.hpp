#pragma once

#include <vector>
#include <string>

class Block;
class Room;

class World {
private:
	Room* room;
	
public:
	World();

	const std::vector<std::vector<Block*>>& get_level_map();
	const Room* get_room();

	bool was_updated{true};
};