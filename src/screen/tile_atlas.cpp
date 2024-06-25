#include "tile_atlas.hpp"

Tile_atlas_fragment::Tile_atlas_fragment(
	int px, int py, int sx, int sy
) :
	px{ px }, py{ py }, sx{ sx }, sy{ sy } {}
Tile_atlas_fragment::Tile_atlas_fragment() :
	px{ 0 }, py{ 0 }, sx{ 0 }, sy{ 0 } {}

//TILE ATLAS

Tile_atlas::Tile_atlas(
	const sf::Texture* texture, 
	int tile_size, 
	const std::map<int, Tile_atlas_fragment>& fragments
) : atlas{ texture }, tile_size{ tile_size }, fragments{fragments} {
	this->fragments[0] = Tile_atlas_fragment(0,0,0,0);
}
Tile_atlas::Tile_atlas(
)
{
	this->fragments[0] = Tile_atlas_fragment(0, 0, 0, 0);
}


const Tile_atlas_fragment& Tile_atlas::get_tile_fragment(int name) const {
	if (fragments.find(name) == fragments.end())
		return fragments.at(0);
	fragments.at(name);
}
const sf::Texture* Tile_atlas::get_texture() const {
	return atlas;
}
int Tile_atlas::get_tile_size() const {
	return tile_size;
}