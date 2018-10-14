#pragma once

#include <Field.hpp>

#include <queue>
#include <list>

class BasicSearch{
public:
    class Node{
    public:
        Field field;
        int turn, count_search;
    };

    int limit_search;
    std::queue<Node> queue;

    BasicSearch();

    virtual void search();
};
