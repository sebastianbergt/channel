#!/usr/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build -S .
cmake --build build
./build/tests/channel_tests
gcovr tests/