#!/bin/bash

export BUILD_DIR="test_build"
export TEST_DIR="../test"
export SRC_DIR="../src"
export INCLUDE_DIR="../include"

if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

gcc -Os -std=c99 -I $INCLUDE_DIR -o $BUILD_DIR/traj_trapez.o -c $SRC_DIR/traj_trapez.c -lm
gcc -Os $BUILD_DIR/traj_trapez.o -I $INCLUDE_DIR -o $BUILD_DIR/test_trapez $TEST_DIR/test_trapez.c -lm
$BUILD_DIR/test_trapez > $BUILD_DIR/trapez_data.csv
cat $BUILD_DIR/trapez_data.csv
python test_trapez.py