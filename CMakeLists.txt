cmake_minimum_required(VERSION 3.23)
project(Lab3_OP)

set(CMAKE_CXX_STANDARD 14)

add_executable(SandPileModel
        main.cpp
        parsingArgs/args.h
        parsingArgs/parsingArgs.cpp
        field/makeField.h
        field/makeField.cpp
        field/field.h
        field/field.cpp
        dispersion/dispersion.h
        dispersion/dispersion.cpp
        picture/picture.cpp
        picture/picture.h)
