@echo off
setlocal

set QT_BIN=C:\Qt\6.8.1\mingw_64\bin

if not exist "%QT_BIN%\qmake.exe" (
    echo Qt not found in %QT_BIN%
    echo Please install Qt and update this path in build.bat
    exit /b 1
)

"%QT_BIN%\qmake.exe" FleetDispatch.pro
mingw32-make

if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build completed successfully.
endlocal
