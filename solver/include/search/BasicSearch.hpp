#pragma once

#include <structure/Field.hpp>
#include <structure/Position.hpp>
#include <structure/Behavior.hpp>

#include <vector>
#include <array>

class BasicSearch{
public:

    int limit_search;

    BasicSearch();

    virtual std::array<Behavior, 2> search(Field field);
};
