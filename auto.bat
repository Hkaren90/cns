@echo off
setlocal enabledelayedexpansion

:menu
cls
echo.
echo =========================
echo     CNS PROGRAM VIEWER
echo =========================
echo.
echo 0. Exit
echo.

set /p exp=Enter Experiment Number: 

if "%exp%"=="0" exit
if "%exp%"=="" goto menu

echo %exp% | findstr /r "^[0-9][0-9]*$" >nul || goto menu

if %exp% LSS 1 goto menu
if %exp% GTR 12 goto menu

cls
echo =========================
echo Experiment %exp%
echo =========================
echo.

curl -s https://api.github.com/repos/Hkaren90/cns/contents/%exp% > temp.txt

for /f "tokens=2 delims=:," %%a in ('findstr /i "\"name\"" temp.txt') do (

    set file=%%~a
    set file=!file:"=!
    set file=!file: =!

    echo ==================================
    echo !file!
    echo ==================================
    echo.

    curl -sL https://raw.githubusercontent.com/Hkaren90/cns/main/%exp%/!file!

    echo.
    echo.
)

del temp.txt

pause
goto menu
