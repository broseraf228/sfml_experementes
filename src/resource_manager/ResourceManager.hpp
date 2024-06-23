#ifndef BS_RESOURCEMANAGER_H
#define BS_RESOURCEMANAGER_H

#include <string>
#include <map>
#include <fstream>

#include "SFML/Graphics.hpp"

class ResourceManager {
private:
	static std::string g_path;
	static std::fstream file;

	static std::string version;

	static std::map<std::string, sf::Image*> images;
	static bool add_to_images(sf::Image* image_ptr, const std::string& name);

	static std::map<std::string, sf::Texture*> textures;
	static bool add_to_textures(sf::Texture* texture_ptr, const std::string& name);

	static std::string readFromFile(const std::string& file_name);
public:
	static int Initialisation(const std::string& path_to_exe);

	static const sf::Image* load_image(const std::string& path, const std::string& name);
	static const sf::Image* get_image(const std::string& name);

	static const sf::Texture* load_texture(const sf::Image*, const sf::IntRect&, const std::string& name);
	static const sf::Texture* get_texture(const std::string& name);

	
};

#endif