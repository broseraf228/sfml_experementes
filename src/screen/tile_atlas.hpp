#pragma once

#include "SFML/Graphics.hpp"
#include <map>

class Tile_atlas {
protected:
	std::map<std::string, sf::IntRect> fragments{};
	int tile_size{ 0 };
	const sf::Texture* atlas{nullptr};
public:
	Tile_atlas(const sf::Texture* texture, int tile_size, const std::map<std::string, sf::IntRect>& fragments);
	Tile_atlas();

	const sf::IntRect& get_tile_fragment(const std::string& name) const;
	const sf::Texture* get_texture() const;
	int get_tile_size() const;
};

class Animation{
protected:
	int dx{0}, dy{0};
	int count{0};
	int sx{0}, sy{0};
	const sf::Texture* texture_ptr{nullptr};

	float frame_time{ 0 };
	float current_time{ 0 };
public:
	Animation(const sf::Texture* texture, int tile_size_x, int tile_size_y, int count, float frame_time = 1, int dx = 0, int dy = 0);
	Animation();
	~Animation();

	void subscribe_animation();

	void update_sprite(sf::Sprite& sprite);

	void update_time(float time);
};