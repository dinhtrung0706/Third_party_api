#!/bin/bash

BUILD_CMD="g++ -fsanitize=address -std=c++17 -o main -Iinclude -Iunit_test -g main.cpp \
src/adapter/*.cpp src/api/*.cpp src/core/*.cpp  unit_test/unit_test.cpp  unit_test/testcase/*.cpp"

echo "Building project Task1 VOTIEN with command:"
echo "$BUILD_CMD"
echo "----------------------------------------"
eval $BUILD_CMD
if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "----------------------------------------"
    echo "To run tests, use one of the following commands:"
    echo "1. Run all tests: ./main "
    echo "2. Run a specific test: ./main nameFunctionUnitTest"
else
    echo "Build failed!"
    exit 1
fi
