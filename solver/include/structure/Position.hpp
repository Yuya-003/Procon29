#pragma once

class Position{
public:
    int x, y;

    Position(int x_ = 0, int y_ = 0) :x(x_), y(y_){}

    bool operator==(Position p){
        return p.x == this->x && p.y == this->y;
    }
};
