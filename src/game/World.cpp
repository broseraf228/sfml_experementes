
#include "World.hpp"
#include "../constants.hpp"

std::vector<Block*> Block::blocks = {
	new Block("air"),
	new Block("rock"),
	new Block("stone"),
};


World::World() {
	generate_level(12, 12);
}

void World::generate_level(int sx, int sy){
	level_map.resize(sx);
	for (auto& item : level_map)
		item.resize(sy);

	float rx = 360.0f / sx * 10, ry = 360.0f / sy * 10;
	for (int x = 0; x < sx; x++)
		for (int y = 0; y < sy; y++)
		{
			
			level_map[x][y] = Block::blocks[rand() % 3]->Clone();
		}
}

const std::vector<std::vector<Block*>>& World::get_level_map() {
	return level_map;
}

std::vector<std::vector<std::string>> World::get_level_map_textures() {
	std::vector<std::vector<std::string>> result(level_map.size(), std::vector<std::string>(level_map[0].size(), ""));
	
	int sx = level_map.size(), sy = level_map[0].size(), free_directions_count = 0;
	bool free_directions[4];
	for (int x = 0; x < sx; x++)
		for (int y = 0; y < sy; y++) {
			free_directions_count = 0;
			result[x][y] = level_map[x][y]->get_texture_name();
		}

	return result;
}

Block::Block(const std::string& texture_name) : texture_name{texture_name} {
	
}
Block* Block::Clone() {
	return new Block(texture_name);
}
const std::string& Block::get_texture_name() {
	return texture_name;
}