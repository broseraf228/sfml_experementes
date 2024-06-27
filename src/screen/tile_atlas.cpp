#include "tile_atlas.hpp"

#include "../game/Game.hpp"

//TILE ATLAS

Tile_atlas::Tile_atlas(
	const sf::Texture* texture, 
	int tile_size, 
	const std::map<std::string, sf::IntRect>& fragments
) : atlas{ texture }, tile_size{ tile_size }, fragments{fragments} {
	this->fragments[""] = sf::IntRect(0, 0, 0, 0);
}
Tile_atlas::Tile_atlas(
)
{
	this->fragments[""] = sf::IntRect(0, 0, 0, 0);
}


const sf::IntRect& Tile_atlas::get_tile_fragment(const std::string& name) const {
	if (fragments.find(name) == fragments.end())
		return fragments.at("");
	fragments.at(name);
}
const sf::Texture* Tile_atlas::get_texture() const {
	return atlas;
}
int Tile_atlas::get_tile_size() const {
	return tile_size;
}

// ANIMATIONS
Animation::~Animation() {
	Game::getInstance()->describe_animation(this);
}
Animation::Animation() {
	
}
Animation::Animation(
	const sf::Texture* texture, 
	int tile_size_x, int tile_size_y, 
	int count, 
	float frame_time, 
	int dx, int dy
) : texture_ptr{ texture }, sx{ tile_size_x }, sy {tile_size_y}, count{ count }, frame_time{frame_time}, dx{ dx }, dy{ dy }
{
	
}
void Animation::subscribe_animation(){
	Game::getInstance()->subscribe_animation(this);
}

void Animation::update_sprite(sf::Sprite& sprite){
	int current_frame = current_time / frame_time;
	sprite.setTexture(*texture_ptr);
	sprite.setTextureRect(sf::IntRect
	(
		dx + sx * current_frame,
		dy,
		sx, 
		sy
	));
}

void Animation::update_time(float time){
	current_time += time;
	if(current_time > frame_time * count)
		current_time -= frame_time * count;
}