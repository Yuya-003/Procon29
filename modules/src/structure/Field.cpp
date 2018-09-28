#include <structure/Field.hpp>

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
	
}
