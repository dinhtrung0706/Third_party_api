@echo off
setlocal enabledelayedexpansion

rem Set the initial build command
set BUILD_CMD=g++ -std=c++17 -o main.exe -Iinclude -Iunit_test -g main.cpp unit_test/unit_test.cpp

rem Append all src\adapter\*.cpp files
for %%f in (src\adapter\*.cpp) do (
    set "BUILD_CMD=!BUILD_CMD! %%f"
)

rem Append all src\api\*.cpp files
for %%f in (src\api\*.cpp) do (
    set "BUILD_CMD=!BUILD_CMD! %%f"
)

rem Append all src\core\*.cpp files
for %%f in (src\core\*.cpp) do (
    set "BUILD_CMD=!BUILD_CMD! %%f"
)

rem Loop through unit_test/testcase/*.cpp files and append them to BUILD_CMD
for %%f in (unit_test\testcase\*.cpp) do (
    set BUILD_CMD=!BUILD_CMD! %%f
)

echo Building project Task1 with command:
echo %BUILD_CMD%
echo ----------------------------------------

rem Execute the build command
%BUILD_CMD%
if %ERRORLEVEL% EQU 0 (
    echo Build successful!
    echo ----------------------------------------
    echo To run tests, use one of the following commands:
    echo 1. Run all tests: main.exe
    echo 2. Run a specific test: main.exe nameFunctionUnitTest
) else (
    echo Build failed!
    exit /b 1
)
