#!/usr/bin/env bash

x86_64-w64-mingw32-g++ "${workspaceRoot}src/main.cpp" \
"${workspaceRoot}src/keyboard.cpp" \
"${workspaceRoot}src/update.cpp" \
"${workspaceRoot}src/draw.cpp" \
"${workspaceRoot}src/init.cpp" \
"${workspaceRoot}src/lists.cpp" \
"-I${workspaceRoot}include" \
"-I${workspaceRoot}../../dependencies/STB_IMAGE/include" \
"-I${workspaceRoot}../../dependencies/GLFW/include" \
"-I${workspaceRoot}../../dependencies/FREEGLUT/include" \
"-I${workspaceRoot}../../dependencies/GLEW/include" \
"-lwinmm" \
"-lopengl32" \
"-lglu32" \
"-L${workspaceRoot}../../dependencies/GLEW/bin/Release/x64" \
"-lglew32" \
"-L${workspaceRoot}../../dependencies/FREEGLUT/bin/x64" \
"-lfreeglut" \
"-L${workspaceRoot}../../dependencies/GLFW/lib-mingw-w64" \
"-lglfw3dll" \
"-o" \
"${workspaceRoot}builds/space_impact"