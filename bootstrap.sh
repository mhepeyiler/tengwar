#!/bin/bash

set -x
mkdir -p build
conan install . --output-folder=build --build=missing -s build_type=Debug
cd build
./conanrun.sh
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug 
cmake --build . && ./test/bin/tengwar_test

bash