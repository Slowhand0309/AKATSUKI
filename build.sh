#!/usr/bin/env bash

if [ -e build ]; then
  rm -rf build
  mkdir build
else
  mkdir build
fi

cd build
cmake ..
make

# copy library's
\cp -f src/projects/ATlib/libATlib.a ../lib/.
\cp -f src/projects/ATgae/libATgae.a ../lib/.
