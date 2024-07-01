#include "Room.hpp"

#include "Block.hpp"

room_map::room_map(const std::vector<std::vector<Block*>>& map) {
	this->map = map;
}
room_map::room_map(const std::vector<std::vector<int>>& imap) {
	map = std::vector(imap.size(), std::vector(imap[0].size(), BlockFactory::newBlock(bsc::BLOCKS(0))));
	for (int x = 0; x < imap.size(); x++)
		for (int y = 0; y < imap[x].size(); y++)
			map[x][y] = BlockFactory::newBlock(bsc::BLOCKS(imap[x][y]));
}
room_map::room_map(){
	map = {};
}
const std::vector<std::vector<Block*>>& room_map::get_map() const {
	return map;
}
std::vector<std::vector<std::string>> room_map::get_map_texture() const{
	std::vector<std::vector<std::string>> result(map.size(), std::vector<std::string>(map[0].size(), ""));

	int sx = map.size(), sy = map[0].size();
	bool free_directions[4];
	for (int x = 0; x < sx; x++)
		for (int y = 0; y < sy; y++) {
			result[x][y] = map[x][y]->get_texture_name();
		}

	return result;
}

Room::Room(const room_map& map){
	m_map = map;
}
const room_map& Room::get_map() const {
	return m_map;
}
std::vector<std::vector<std::string>> Room::get_map_textures() const{
	return m_map.get_map_texture();
}