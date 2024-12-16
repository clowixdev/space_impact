#!/usr/bin/env bash

x86_64-w64-mingw32-gcc "${workspaceRoot}src/main.c" "-g" "--std=c99" \
"${workspaceRoot}src/keyboard.c" \
"${workspaceRoot}src/update.c" \
"${workspaceRoot}src/draw.c" \
"${workspaceRoot}src/init.c" \
"${workspaceRoot}src/lists.c" \
"-I${workspaceRoot}include" \
"-I${workspaceRoot}../dependencies/STB_IMAGE/include" \
"-I${workspaceRoot}../dependencies/GLFW/include" \
"-I${workspaceRoot}../dependencies/FREEGLUT/include" \
"-I${workspaceRoot}../dependencies/GLEW/include" \
"-lwinmm" \
"-lopengl32" \
"-lglu32" \
"-L${workspaceRoot}../dependencies/GLEW/bin/Release/x64" \
"-lglew32" \
"-L${workspaceRoot}../dependencies/FREEGLUT/bin/x64" \
"-lfreeglut" \
"-L${workspaceRoot}../dependencies/GLFW/lib-mingw-w64" \
"-lglfw3dll" \
"-o" \
"${workspaceRoot}builds/windows/space_impact"