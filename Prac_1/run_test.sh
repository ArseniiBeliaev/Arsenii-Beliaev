#!/bin/bash

cd PrintLengthMaxPrefix_test
mkdir build
cd build
cmake ..
make
./MaxLength_test
cd ..
rm -r build
