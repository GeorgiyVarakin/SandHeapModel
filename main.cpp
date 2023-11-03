#include <iostream>
#include "parsingArgs/args.h"
#include "field/makeField.h"
#include "dispersion/dispersion.h"
#include "picture/picture.h"

int main(int argc, char *argv[]) {
    args args(argc, argv);

    Field Field = makeField(args.inputDirectory);

    dispersion(Field, args);
}