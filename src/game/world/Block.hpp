#pragma once

#include <string>
#include <vector>

#include "../../constants.hpp"

class Block { // добавить выбор текстуры в зависимости от соседних блоков
protected:
	std::string texture_name;
public:
	Block(const std::string& texture_name);
	virtual Block* Clone();

	virtual const std::string& get_texture_name() const;

	static std::vector<Block*> blocks;
};
class BlockFactory {
public:
	static Block* newBlock(enum class bsc::BLOCKS blockName);
};