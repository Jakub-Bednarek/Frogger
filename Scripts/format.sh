#! /bin/bash

PROJECT_SOURCE_DIR=$(pwd)/Source/Frogger

FILES=$(find $PROJECT_SOURCE_DIR -type f -name "*.cpp" -o -name "*.h")

clang-format --style=file:.clang-format -i $FILES