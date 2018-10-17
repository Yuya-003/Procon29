#pragma once

class Behavior{
public:
    enum Action{
        move, stay, erase
    };s

    enum Dir{
        up, down, left, right, upleft, upright, downleft, downright, none
    };

    Action action;
    Dir dir;
};
