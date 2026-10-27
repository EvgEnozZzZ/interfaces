@echo off
setlocal

set APP_PATH=%~dp0release\FleetDispatch.exe
if not exist "%APP_PATH%" (
    set APP_PATH=%~dp0debug\FleetDispatch.exe
)

if not exist "%APP_PATH%" (
    echo Executable not found. Please build the project first.
    exit /b 1
)

start "FleetDispatch" "%APP_PATH%"
endlocal
