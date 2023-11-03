#pragma once

#include "field.h"

void checkCoords(std::pair<int, int> &coords, int value);

struct inputCoords {
    int x, y;
    uint64_t cnt;
};

Field makeField(std::string inputDirectory);