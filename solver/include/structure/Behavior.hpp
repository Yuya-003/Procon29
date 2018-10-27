#pragma once

class Behavior{
public:
    enum Action{
        move, stay, erase
    };

    enum Dir{
        up, down, left, right, upleft, upright, downleft, downright, none
    };

    Action action;
    Dir dir;
};
