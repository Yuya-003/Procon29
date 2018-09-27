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

    std::vector<std::vector<Cell>> c;

public:

	Field(size_t h, size_t w);
	std::vector<Cell> operator[] (size_t i);
};
