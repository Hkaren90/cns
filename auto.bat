@echo off
setlocal enabledelayedexpansion

:menu
cls
echo =========================
echo        CNS VIEWER
echo =========================
echo.
echo 0. Exit
echo.

set /p exp=Enter Experiment Number: 

if "%exp%"=="0" exit
if "%exp%"=="" goto menu

echo %exp% | findstr /r "^[0-9][0-9]*$" >nul || goto menu

cls
echo =========================
echo Experiment %exp%
echo =========================
echo.

curl -s https://api.github.com/repos/Hkaren90/cns/contents/%exp% > temp.json

for /f "tokens=*" %%a in ('findstr /i "download_url" temp.json') do (

    set line=%%a

    set line=!line:*https=https!
    set line=!line:",=!

    echo ==================================
    echo FILE
    echo ==================================
    echo.

    curl -sL "!line!"

    echo.
    echo.
)

del temp.json

pause
goto menu
