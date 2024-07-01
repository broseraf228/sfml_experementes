
#include "ResourceManager.hpp"

#include <iostream>

#include "../game/world/Room.hpp"
#include "../screen/tile_atlas.hpp"

std::string ResourceManager::g_path = "?";
std::fstream ResourceManager::file = std::fstream();
std::string ResourceManager::version = "?";
AssetManager* ResourceManager::asset = nullptr;

std::map<std::string, sf::Image*> ResourceManager::images = {};
std::map<std::string, sf::Texture*> ResourceManager::textures = {};

int ResourceManager::Initialisation(const std::string& path_to_exe) {
	g_path = path_to_exe + "res\\";

	version = readFromFile("version.txt");
	if (version == "") {
		std::cout << "resources folder or version file not found" << std::endl;
		return 1;
	}

	asset = new AssetManager();

	return 0;
}

std::string ResourceManager::readFromFile(const std::string& file_name) {
	file.open(g_path + file_name, std::ios::in);
	if (!file.is_open())
		return "";
	std::string data = "";
	std::string line = "";
	while (std::getline(file, line))
		data += line;
	file.close();
	return data;
}

bool ResourceManager::add_to_images(sf::Image* image_ptr, const std::string& name)
{
	if (images.find(name) != images.end())
		return false;
	images[name] = image_ptr;
}
const sf::Image* ResourceManager::load_image(const std::string& path, const std::string& name)
{
	sf::Image* image = new sf::Image();
	if (!image->loadFromFile(g_path + path)) {
		delete image;
		std::cout << "image \"" << g_path + path << "\" file is not exist";
		return nullptr;
	}
	add_to_images(image, name);
	return image;
}
const sf::Image* ResourceManager::get_image(const std::string& name)
{
	if (images.find(name) == images.end()) {
		std::cout << "called unloaded image \"" << name << "\" " << std::endl;
		throw std::exception();
		return nullptr;
	}
	return images[name];
}

bool ResourceManager::add_to_textures(sf::Texture* texture_ptr, const std::string& name){
	if (images.find(name) != images.end())
		return false;
	textures[name] = texture_ptr;
}
const sf::Texture* ResourceManager::load_texture(const sf::Image* image, const sf::IntRect& intrect, const std::string& name) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromImage(*image, intrect)) {
		std::cout << "can't load texture \"" << name << "\" from image" << std::endl;
		delete texture;
		return nullptr;
	}
	add_to_textures(texture, name);
	return texture;
}
const sf::Texture* ResourceManager::get_texture(const std::string& name) {
	if (textures.find(name) == textures.end()) {
		std::cout << "called unloaded texture \"" << name << "\" " << std::endl;
		throw std::exception();
		return nullptr;
	}
	return textures[name];
}





room_template::room_template(const room_map& map, const Tile_atlas* blocks, const Tile_atlas* decorations) : 
	blocks{blocks}, decorations{decorations}
{
	rm = new room_map(map);
}

AssetManager::AssetManager() {

	ResourceManager::load_image("img\\blocks\\level_1.png", "i_level_1");
	ResourceManager::load_texture(ResourceManager::get_image("i_level_1"), sf::IntRect(0, 0, 128, 128), "te_level_1");

	ResourceManager::load_image("img\\animations\\player_animations.png", "i_player_animations");
	ResourceManager::load_texture(ResourceManager::get_image("i_player_animations"), sf::IntRect(0, 0, 128, 128), "te_player_animation");

	ResourceManager::load_image("img\\rooms\\default.png", "i_rb_default");
	ResourceManager::load_texture(ResourceManager::get_image("i_rb_default"), sf::IntRect(0, 0, 128, 128), "te_room_background_default");


	//load tile_atlases
	int ds = 24;
	Tile_atlas* tile_atlas = new Tile_atlas(ResourceManager::get_texture("te_level_1"), ds,
		{
			{"air" , texRect(0,  0, ds, ds)},
			{"rock" , texRect(24, 0, ds, ds)},
			{"stone" , texRect(48, 0, ds, ds)},
		}
	);
	tile_atlas_s["blocks_default"] = tile_atlas;
	tile_atlas = new Tile_atlas(ResourceManager::get_texture("te_room_background_default"), ds,
		{
			{"lt" , texRect(0,  0,	 ds, ds)},
			{"t" , texRect(24, 0,	 ds, ds)},
			{"rt" , texRect(48, 0,	 ds, ds)},
			{"l" , texRect(0,  ds, ds, ds)},
			{"m" , texRect(24, ds, ds, ds)},
			{"r" , texRect(48, ds, ds, ds)},
			{"lb" , texRect(0,  48, ds, ds)},
			{"b" , texRect(24, 48, ds, ds)},
			{"rb" , texRect(48, 48, ds, ds)},
		}
	);
	tile_atlas_s["room_decorations_default"] = tile_atlas;

	//load animations
	Animation* animation = new Animation(ResourceManager::get_texture("te_player_animation"), 16, 16, 2);
	animation_s["player_animation"] = animation;

	//room templates
	std::vector<room_template> rt_s{};

	room_map map({ {1,0,0,1}, {1,0,0,1}, {0,0,0,2}, {1, 2, 2, 0}, {2, 2, 2, 2} });
	room_template rt(map, nullptr, nullptr);
	rt_s.push_back(rt);

	map = room_map({ {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} });
	rt = room_template(map, nullptr, nullptr);
	rt_s.push_back(rt);

	room_template_s[bsc::ROOMS::Default] = rt_s;
	
}
const room_template* AssetManager::get_room_template(bsc::ROOMS name) {
	if (room_template_s.find(name) == room_template_s.end())
		return nullptr;
	
	return &room_template_s[name][rand() % room_template_s[name].size()];
}
const Tile_atlas* AssetManager::get_tile_atlas(const std::string& name) {
	if (tile_atlas_s.find(name) == tile_atlas_s.end())
		return nullptr;
	return tile_atlas_s[name];
}
const Animation* AssetManager::get_animation(const std::string& name){
	if (animation_s.find(name) == animation_s.end())
		return nullptr;
	return animation_s[name];
}