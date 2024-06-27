#pragma once

#include <vector>
#include <string>

class Block;

class World {
private:
	std::vector<std::vector<Block*>> level_map;
	void generate_level(int sx, int sy);

	int x_in_map(int x);
	int y_in_map(int y);
public:
	struct block_graphick_data {
		int name, state;
	};
	World();

	const std::vector<std::vector<Block*>>& get_level_map();
	std::vector<std::vector<std::string>> get_level_map_textures();

	bool was_updated{true};
};

class Block {
protected:
	std::string texture_name;
public:
	Block(const std::string& texture_name);
	virtual Block* Clone();

	virtual const std::string& get_texture_name();

	static std::vector<Block*> blocks;
};