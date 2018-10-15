#pragma once

#include <structure/Cell.hpp>
#include <structure/Position.hpp>

#include <cmath>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>

class Field {
public:
	std::vector<std::vector<Cell>> cells; //マス目上の配列
	std::array<Position, 2> team1; //味方エージェントの居場所
	std::array<Position, 2> team2; //相手エージェントの居場所

	Field(size_t h = 0, size_t w = 0);
	void resize(size_t h, size_t w);
	size_t rowSize(); //列数(横の幅)
	size_t colSize(); //行数(縦の幅)

	int calcScore(Cell::Status status); //team:1(自分),2(相手)
};
