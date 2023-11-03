#include <iostream>
#include "dispersion.h"
#include "../picture/picture.h"

namespace M {
    std::pair<int, int> move[4]{{0,  1},
                                {0,  -1},
                                {1,  0},
                                {-1, 0}};
    int moveSize = 4;
    int numberPicture = 1;
}
using namespace M;

void dispersion(Field &field, args &args) {
    for (int i = 1; i <= args.maxIter; ++i) {
        bool withoutChanges = true;
        newIteration(field, withoutChanges);

        if (withoutChanges) {
            break;
        }

        if (args.freq != 0 and i % args.freq == 0) {
            inBMPPicture(field, args.outputDirectory);
        }
    }

    inBMPPicture(field, args.outputDirectory);
}

void newIteration(Field &Field, bool &withoutChanges) {
    for (int i = Field.ys.first; i <= Field.ys.second; ++i) {
        for (int j = Field.xs.first; j <= Field.xs.second; ++j) {
            int cI = i + Field.coordsShift.first,
                    cJ = j + Field.coordsShift.second;

            if (Field.field[cI][cJ] < 4) {
                continue;
            }

            withoutChanges = false;

            checkFieldBorder(Field, j, i);

            cI = i + Field.coordsShift.first;
            cJ = j + Field.coordsShift.second;

            for (int z = 0; z < M::moveSize; ++z) {
                int newI = cI + M::move[z].first,
                        newJ = cJ + M::move[z].second;

                Field.field[newI][newJ]++;
            }

            Field.field[cI][cJ] -= 4;
        }
    }
}

void checkFieldBorder(Field &Field, int x, int y) {
    for (int z = 0; z < M::moveSize; ++z) {
        int newX = x + M::move[z].first,
                newY = y + M::move[z].second;

        if (!onTheField(Field, newX, newY)) {
            Field.update(newX, newY, 0);
        }
    }
}

bool onTheField(Field &Field, int x, int y) {
    return (x >= Field.xs.first and x <= Field.xs.second) and (y >= Field.ys.first and y <= Field.ys.second);
}

void inBMPPicture(Field &Field, std::string &outputDirectory) {
    int widthBMP = Field.xs.second - Field.xs.first + 1;
    int heightBMP = Field.ys.second - Field.ys.first + 1;

    sandPicture Picture(widthBMP, heightBMP);
    const Color colors[] = {Color::white(), Color::green(), Color::yellow(), Color::violet(), Color::black()};

    for (int y = Field.ys.first; y <= Field.ys.second; y++) {
        for (int x = Field.xs.first; x <= Field.xs.second; x++) {

            int curY = y + Field.coordsShift.first;
            int curX = x + Field.coordsShift.second;

            if (Field.field[curY][curX] < 4) {
                Picture.SetColor(colors[Field.field[curY][curX]], curX, curY);
            } else {
                Picture.SetColor(colors[4], curX, curY);
            }
        }
    }


    std::string filename = outputDirectory + std::to_string(numberPicture);
    numberPicture++;
    filename += ".bmp";

    Picture.Export(filename);
}