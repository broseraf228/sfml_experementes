#include "Block.hpp"

Block::Block(const std::string& texture_name) : texture_name{ texture_name } {

}
Block* Block::Clone() {
	return new Block(texture_name);
}
const std::string& Block::get_texture_name() const {
	return texture_name;
}

Block* BlockFactory::newBlock(enum class bsc::BLOCKS blockName) {
	switch (blockName)
	{
	case bsc::BLOCKS::Air:
		return new Block("air");
		break;
	case bsc::BLOCKS::Rock:
		return new Block("rock");
		break;
	case bsc::BLOCKS::Stone:
		return new Block("stone");
		break;
	}
}