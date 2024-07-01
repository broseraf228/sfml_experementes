#pragma once

#include <vector>
#include <string>
#include <map>

#include "SFML/Graphics.hpp"

#include "../../constants.hpp"
#include "../../screen/tile_atlas.hpp"

class Block;


struct room_map {
private:
	std::vector<std::vector<Block*>> map;
public:
	room_map(const std::vector<std::vector<Block*>>& map);
	room_map(const std::vector<std::vector<int>>& map);
	room_map();

	const std::vector<std::vector<Block*>>& get_map() const;
	std::vector<std::vector<std::string>> get_map_texture() const;
};

class Room {
protected:
	room_map m_map;

public:
	Room(const room_map& map);

	const room_map& get_map() const;
	std::vector<std::vector<std::string>> get_map_textures() const;
};