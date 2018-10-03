#pragma once

#include <vector>

class Field {
public:
	enum Status {
		none
	};
    
private:

    class Cell{
    public:
        int point;
        Status status;
    };

public:

	std::vector<std::vector<Cell>> cells;

	Field(size_t h = 0, size_t w = 0);
	void resize(size_t h, size_t w);
};
