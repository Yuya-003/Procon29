#pragma once

class Cell {
public:
	enum Status {
		none, team1, team2 //自分たちをteam1とする
	};

	int point;
	Status status;
};