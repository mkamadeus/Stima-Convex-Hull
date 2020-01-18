@echo off

call "compile.bat"
if errorlevel 1 goto done

main.exe

:done
