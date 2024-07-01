
#include "World.hpp"

#include "../../resource_manager/ResourceManager.hpp"
#include "Block.hpp"
#include "Room.hpp"

World::World() {
	room = new Room(*ResourceManager::asset->get_room_template(bsc::ROOMS::Default)->rm);
}



const std::vector<std::vector<Block*>>& World::get_level_map() {
	return room->get_map().get_map();
}

const Room* World::get_room() {
	return room;
}

