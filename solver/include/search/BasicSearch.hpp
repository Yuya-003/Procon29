#pragma once

#include <structure/Field.hpp>
#include <structure/Position.hpp>
#include <structure/Behavior.hpp>

#include <vector>
#include <array>
#include <cmath>

class BasicSearch{
public:

    class Node{
    public:

        enum Status{
            none, open, closed
        };

        Status status;
        Position p;
        Cell cell;
        int h_cost; //ヒューリスティクスコスト = 目的地までの距離
        int cost; //実コスト = 今までかかったコスト
        int score; //スコア = h_cost + cost - Cellのpoint
        Node *parent; //親ノード
    };

    int limit_search;
    int border_score = 10;

    BasicSearch();

    virtual std::array<Behavior, 2> search(Field field);
};
