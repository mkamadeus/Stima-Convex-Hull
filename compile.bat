@echo off

echo Compiling...
g++ main.cpp -lfreeglut -lopengl32 -lglu32 -o main.exe