#!/bin/bash

g++ lox.cpp error_handler.cpp token.cpp scanner.cpp object.cpp \
            error_handler.h tokentype.h token.h scanner.h object.h \
            -v -o obnox
./obnox
