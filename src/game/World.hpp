#pragma once

#include <vector>
#include <string>

class Block;

class World {
private:
	std::vector<std::vector<Block*>> level_map;
	void generate_level(int sx, int sy);
public:
	World();

	const std::vector<std::vector<Block*>>& get_level_map();
	std::vector<std::vector<int>> get_level_map_textures();

	bool was_updated{true};
};

class Block {
protected:
	int texture_name;
public:
	Block(int texture_name);
	virtual Block* Clone();

	virtual int get_texture_name();

	static std::vector<Block*> blocks;
};