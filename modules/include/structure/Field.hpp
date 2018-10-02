#pragma once

#include <vector>
#include <structure/Cell.hpp>

class Field {
public:
	std::vector<std::vector<Cell>> cells;

	Field(size_t h = 0, size_t w = 0);
	void resize(size_t h, size_t w);
	size_t rowSize(); //行数
	size_t colSize(); //列数
};
