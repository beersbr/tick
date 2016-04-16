#!/bin/bash

BASE_DIR="src/"
BUILD_DIR="build/"
BUILD_FLAGS=""
OUTPUT_NAME="tick_debug_$(date +%s)"
DEBUG_SWITCHES="DEBUG"
FRAMEWORK_DIRECTORY="/Users/brettbeers/frameworks"

clang++ -c $BASE_DIR"hogl.cpp" -g -o hogl.o -D $DEBUG_SWITCHES 
clang++ -c $BASE_DIR"animations.cpp" -g -o animations.o -D $DEBUG_SWITCHES

clang++ -c -fPIC -g -o game.o $BASE_DIR"game.cpp"
clang++ -shared -fPIC -o libgame.so game.o hogl.o -lc -F $FRAMEWORK_DIRECTORY -framework SDL2 -framework OpenGL

clang++ -F $FRAMEWORK_DIRECTORY -framework SDL2 -framework OpenGL -D $DEBUG_SWITCHES \
-o $BUILD_DIR/$OUTPUT_NAME -g $BASE_DIR"main.cpp" animations.o hogl.o

#NOTE(Brett): if there are more than 5 build than delete the oldest one and link the newest one
BUILD_COUNT=$(ls -al $BUILD_DIR/tick_debug_* | wc -l | awk '{print $1}')
if [ $BUILD_COUNT -gt 5 ]; then
	tv=$(ls -al $BUILD_DIRtick_debug_* | sed -n '1p' | awk '{print $9}')
	echo $tv
	rm $tv
fi

rm tick_debug
ln -s $BUILD_DIR/$OUTPUT_NAME tick_debug

rm *.o