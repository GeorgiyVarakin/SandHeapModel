#pragma once

struct args {
    std::string inputDirectory;
    std::string outputDirectory;
    int maxIter = 1000;
    int freq = 0;

    args(int argc, char *argv[]);
};