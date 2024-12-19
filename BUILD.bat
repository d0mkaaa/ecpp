@echo off
if not exist build mkdir build
g++ -std=c++17 -I./src/core -I./src/ast src/main.cpp src/core/*.cpp -o build/ecpp.exe
if %errorlevel% equ 0 (
    echo Build successful!
) else (
    echo Build failed!
)