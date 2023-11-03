#pragma once

struct Field {
    uint64_t **field;
    std::pair<int, int> xs, ys, coordsShift {0,0};

    Field(std::pair<int,int> x, std::pair<int,int> y);

    void updateSize(int x, int y);

    void update(int x, int y, uint64_t value);

    void print();
};