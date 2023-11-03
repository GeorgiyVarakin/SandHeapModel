#include <iostream>
#include "args.h"

args::args(int argc, char *argv[]) {
    std::string argName, argValue;
    for (int i = 1; i < argc; i += 2) {
        argName = argv[i];
        argValue = argv[i + 1];

        if (argName.size() > 2) {
            argName[1] = argName[2];
        }

        if (argName[1] == 'i') {
            inputDirectory = argValue;
        }
        if (argName[1] == 'o') {
            outputDirectory = argValue;
        }
        if (argName[1] == 'm') {
            maxIter = stoi(argValue);
        }
        if (argName[1] == 'f') {
            freq = stoi(argValue);
        }

        argName.clear();
        argValue.clear();
    }

    if (inputDirectory == "" or outputDirectory == "") {
        std::cout << "ERROR: one or both directories are not given\n";
        exit(0);
    }
}