@echo off

call "compile.bat"
if errorlevel 1 goto done

cd bin
main.exe
cd ../

:done
