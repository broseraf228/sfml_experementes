
#include "ResourceManager.hpp"

#include <iostream>

std::string ResourceManager::g_path = "?";
std::fstream ResourceManager::file = std::fstream();
std::string ResourceManager::version = "?";

std::map<std::string, sf::Image*> ResourceManager::images = {};
std::map<std::string, sf::Texture*> ResourceManager::textures = {};

int ResourceManager::Initialisation(const std::string& path_to_exe) {
	g_path = path_to_exe + "res\\";

	version = readFromFile("version.txt");
	if (version == "") {
		std::cout << "resources folder or version file not found" << std::endl;
		return 1;
	}

	load_image("textures\\textures.png", "player_textures");
	load_texture(get_image("player_textures"), sf::IntRect(0, 0, 16, 16), "playerState_1");
	load_texture(get_image("player_textures"), sf::IntRect(16, 0, 16, 16), "playerState_2");

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