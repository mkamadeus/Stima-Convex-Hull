@echo off

echo Compiling...
g++ src/main.cpp -lfreeglut -lopengl32 -lglu32 -o bin/main.exe