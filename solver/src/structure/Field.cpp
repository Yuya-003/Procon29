#include <structure/Field.hpp>

Field::Field(size_t h, size_t w)
{
	for (int i = 0; i < h; i++) {
		this->cells.push_back(std::vector<Cell>(w));
	}
}

void Field::resize(size_t h, size_t w)
{
	this->cells.resize(h);
	for (int i = 0; i < cells.size(); i++) {
		cells[i].resize(w);
		cells[i].shrink_to_fit();
	}
	this->cells.shrink_to_fit();
}
