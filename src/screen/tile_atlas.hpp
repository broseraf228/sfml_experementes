#pragma once

#include "SFML/Graphics.hpp"
#include <map>

struct Tile_atlas_fragment {
	Tile_atlas_fragment(int px, int py, int sx, int sy);
	Tile_atlas_fragment();
	int px, py, sx, sy;
};
class Tile_atlas {
private:
	std::map<int, Tile_atlas_fragment> fragments;
	int tile_size;
	const sf::Texture* atlas;
public:
	Tile_atlas(const sf::Texture* texture, int tile_size, const std::map<int, Tile_atlas_fragment>& fragments);
	Tile_atlas();

	const Tile_atlas_fragment& get_tile_fragment(int name) const;
	const sf::Texture* get_texture() const;
	int get_tile_size() const;
};