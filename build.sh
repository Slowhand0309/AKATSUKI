#!/bin/sh

mkdir build
cd build
cmake ..
make

# copy library's
\cp -f src/projects/ATlib/libATlib.a ../lib/.
