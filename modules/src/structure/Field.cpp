#include <structure/Field.hpp>
#include <iostream>

Field::Field(size_t h, size_t w)
{
	for (int i = 0; i < h; i++) {
		this->c.push_back(std::vector<Cell>(w));
	}
}

std::vector<Field::Cell> Field::operator[](size_t i)
{
	return this->c[i];
}

void Field::resize(size_t h, size_t w)
{
	this->c.resize(h);
	for (int i = 0; i < c.size(); i++) {
		c[i].resize(w);
		c[i].shrink_to_fit();
	}
	this->c.shrink_to_fit();
}
