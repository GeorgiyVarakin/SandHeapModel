#pragma once

#include "../Field/field.h"
#include "../parsingArgs/args.h"

void dispersion(Field &field, args &args);

void newIteration(Field &Field, bool &withoutChanges);

void checkFieldBorder(Field &Field, int x, int y);

bool onTheField(Field &Field, int x, int y);

void inBMPPicture(Field &Field, std::string &outputDirectory);