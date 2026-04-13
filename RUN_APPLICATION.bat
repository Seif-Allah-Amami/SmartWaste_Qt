@echo off
REM Run the Employee Management Application
REM This script sets up the Qt environment and launches the application

setlocal enabledelayedexpansion

REM Set Qt environment paths
set QT_PATH=C:\Qt\6.7.3\mingw_64
set MINGW_PATH=C:\Qt\Tools\mingw1120_64

REM Add Qt and MinGW to PATH
set PATH=%QT_PATH%\bin;%MINGW_PATH%\bin;%PATH%

REM Change to release directory
cd /d "%~dp0release"

echo =========================================
echo Employee Management System
echo =========================================
echo.
echo Oracle Database Connection Details:
echo - Host: localhost
echo - Port: 1521
echo - SID: xe
echo - Username: houda
echo - Password: root
echo.
echo Starting application...
echo.

REM Run the application
version1.exe

REM If application exits, show status
if %errorlevel% equ 0 (
    echo.
    echo Application closed successfully
) else (
    echo.
    echo Application exited with error code: %errorlevel%
    pause
)

endlocal
