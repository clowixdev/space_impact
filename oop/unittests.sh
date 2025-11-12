#!/usr/bin/env bash

g++ "${workspaceRoot}src/unittests.cpp" \
"${workspaceRoot}src/classes/asteroid.cpp" \
"${workspaceRoot}src/classes/bullet.cpp" \
"${workspaceRoot}src/classes/player.cpp" \
"${workspaceRoot}src/classes/boss.cpp" \
"${workspaceRoot}src/classes/heart.cpp" \
"-I${workspaceRoot}include" \
"-lgtest" \
"-o" \
"${workspaceRoot}builds/tests"

./builds/tests