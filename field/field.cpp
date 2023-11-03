#include <iostream>
#include "field.h"

void changeCoords(std::pair<int, int> &coords, int value) {
    coords.first = std::min(coords.first, value);
    coords.second = std::max(coords.second, value);
}

Field::Field(std::pair<int, int> x, std::pair<int, int> y) {
    coordsShift = {-y.first, -x.first};

    xs = x;
    ys = y;

    field = new uint64_t *[(ys.second - ys.first) + 1];

    for (int i = ys.first; i <= ys.second; ++i) {
        field[i + coordsShift.first] = new uint64_t[(xs.second - xs.first) + 1];
        for (int j = xs.first; j <= xs.second; ++j) {
            field[i + coordsShift.first][j + coordsShift.second] = 0;
        }
    }
}


void Field::updateSize(int x, int y) {
    std::pair<int, int> newX = xs;
    std::pair<int, int> newY = ys;

    changeCoords(newX, x);
    changeCoords(newY, y);

    std::pair<int, int> newShift = coordsShift;
    if (y + coordsShift.first < 0)
        ++newShift.first;
    if (x + coordsShift.second < 0)
        ++newShift.second;

    uint64_t **newField = new uint64_t *[(newY.second - newY.first) + 1];

    for (int i = newY.first; i <= newY.second; ++i) {
        int cI = i + newShift.first;
        newField[cI] = new uint64_t[(newX.second - newX.first) + 1];
        for (int j = newX.first; j <= newX.second; ++j) {
            int cJ = j + newShift.second;
            if (ys.first <= i and i <= ys.second and xs.first <= j and j <= xs.second) {
                newField[cI][cJ] = field[i + coordsShift.first][j + coordsShift.second];
            } else {
                newField[cI][cJ] = 0;
            }
        }
    }

    field = newField;
    xs = newX;
    ys = newY;
    coordsShift = newShift;
}

void Field::update(int x, int y, uint64_t value) {
    if (y < ys.first or y > ys.second or x < xs.first or x > xs.second) {
        updateSize(x, y);
    }

    field[y + coordsShift.first][x + coordsShift.second] = value;
}