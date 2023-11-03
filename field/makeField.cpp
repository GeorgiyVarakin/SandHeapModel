#include <iostream>
#include <fstream>
#include "makeField.h"

void checkCoords(std::pair<int, int> &coords, int value) {
    coords.first = std::min(coords.first, value);
    coords.second = std::max(coords.second, value);
}

Field makeField(std::string inputDirectory) {
    std::ifstream file(inputDirectory);

    const int min_size = -33000, max_size = 33000;
    std::pair<int, int> Xs{max_size, min_size};
    std::pair<int, int> Ys{max_size, min_size};

    if (!file.is_open()) {
        std::cout << "ERROR READING FILE.";
        exit(0);
    }

    inputCoords* queue = new inputCoords[1000];
    int queueSize = 0;

    while (!file.eof()) {
        int x, y;
        uint64_t cnt;
        file >> x >> y >> cnt;

        checkCoords(Xs, x);
        checkCoords(Ys, y);

        queue[queueSize].x = x;
        queue[queueSize].y = y;
        queue[queueSize].cnt = cnt;

        ++queueSize;
    }

    /*for(int i = 0; i < queueSize; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << queue[i][j] << ' ';
        std::cout << '\n';
    }*/

    Field field{Xs, Ys};

    for(int i = 0; i < queueSize; ++i) {
        field.update(queue[i].x, queue[i].y, queue[i].cnt);
    }

    return field;
}