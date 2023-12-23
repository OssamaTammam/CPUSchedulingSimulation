#!/bin/bash

# Shell script to generate Makefile using CMake and build the project

# Create build directory
mkdir -p build
cd build

# Run CMake to generate Makefile
cmake ..

# Build the project using make
make

# Run the executable (if applicable)
./CPU_SCHEDULING
