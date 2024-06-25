
#include "World.hpp"
#include "../constants.hpp"

std::vector<Block*> Block::blocks = {
	new Block(int(bsc::BLOCKS::Air)),
	new Block(int(bsc::BLOCKS::Rock)),
};


World::World() {
	generate_level(10, 10);
}

void World::generate_level(int sx, int sy){
	level_map.resize(sx);
	for (auto& item : level_map)
		item.resize(sy);

	float rx = 360.0f / sx;
	for (int x = 0; x < sx; x++)
		for (int y = 0; y < sy; y++)
		{
			if (sin(x * rx + y) > 0)
				level_map[x][y] = Block::blocks[0]->Clone();
			if (sin(x * rx + y) <= 0)
				level_map[x][y] = Block::blocks[1]->Clone();
		}
}

const std::vector<std::vector<Block*>>& World::get_level_map() {
	return level_map;
}
std::vector<std::vector<int>> World::get_level_map_textures() {
	std::vector<std::vector<int>> result( 10, std::vector<int>(10, 0));
	for (int x = 0; x < level_map.size(); x++)
		for (int y = 0; y < level_map[x].size(); y++)
			result[x][y] = level_map[x][y]->get_texture_name();

	return result;
}

Block::Block(int texture_name) : texture_name{texture_name} {
	
}
Block* Block::Clone() {
	return new Block(texture_name);
}
int Block::get_texture_name() {
	return texture_name;
}