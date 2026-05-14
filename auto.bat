@echo off
setlocal enabledelayedexpansion

:menu
cls
echo.
echo "enter the exp number"
echo 0. Exit
echo.
set /p exp=Enter Experiment Number: 

if "%exp%"=="0" (
    cls
    doskey /reinstall >nul 2>&1
    del "%~f0"
    exit
)
if "%exp%"=="" goto menu
if %exp% LSS 0 goto menu
if %exp% GTR 10 goto menu

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
    curl -sL https://raw.githubusercontent.com/Hkaren90/cns/main/%exp%/!file!
    echo.
    echo.
)

del temp.txt
pause
goto menu
